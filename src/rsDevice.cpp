#include "rsInstance.hpp"
#include "rsQueue.hpp"
#include "rsSwapChain.hpp"

#include <stdexcept>
#include <cstdint>
#include <set>

#include <vulkan/vulkan.hpp>

namespace RS{
    void rsInstance::pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface){
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(instance,&physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(instance,&physicalDeviceCount, physicalDevices.data());

        for(const auto& currentPhysicalDevice : physicalDevices){
            if(isDeviceSuitable(currentPhysicalDevice, surface)){
                physicalDevice = currentPhysicalDevice;
                break;
            }
        }
        if(physicalDevice == VK_NULL_HANDLE){
            throw std::runtime_error("Failed to find suitable GPU");
        }
    }

    bool rsInstance::isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface){
        rsQueue graphicsQueue;
        QueueFamilyIndices indices = graphicsQueue.FindQueueFamily(physicalDevice, surface);

        VkPhysicalDeviceFeatures deviceFeatures;
        VkPhysicalDeviceProperties deviceProperties;

        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        m_extensionSupport = checkDeviceExtensionSupport(physicalDevice);

        bool swapChainAdequate = false;

        if(m_extensionSupport){
            SwapChainSupportDetails swapChainSupport;
            swapChainSupport = swapChainSupport.querySwapChainSupport(physicalDevice, surface);

            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return deviceProperties.deviceType == indices.isComplete() && m_extensionSupport && swapChainAdequate;
    }

    bool rsInstance::checkDeviceExtensionSupport(VkPhysicalDevice device){
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtension(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,availableExtension.data());

        std::set<std::string> requiredExtension(m_DeviceFeatures.begin(), m_DeviceFeatures.end());

        for(const auto &extension : availableExtension){
            requiredExtension.erase(extension.extensionName);
        }

        return requiredExtension.empty();
    }

    void rsInstance::createLogicalDevice(VkSurfaceKHR surface){
        rsQueue graphicsQueue;

        QueueFamilyIndices indices = graphicsQueue.FindQueueFamily(physicalDevice, surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        float queuePriority = 1.0f;
        for(uint32_t queueFamily : uniqueQueueFamilies){
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        std::vector<const char*> deviceExtensions = {
            "VK_KHR_portability_subset",
        };

        deviceExtensions.insert(deviceExtensions.end(), m_DeviceFeatures.begin(), m_DeviceFeatures.end());

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = 1;
       
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if(enableValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.validationLayers.size());
            createInfo.ppEnabledLayerNames = m_ValidationLayers.validationLayers.data();
        } else{
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &device);
        if(result != VK_SUCCESS){
            throw std::runtime_error("Failed to create logicial device error code: " + std::to_string(result) + "!");
        }

        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }
}
