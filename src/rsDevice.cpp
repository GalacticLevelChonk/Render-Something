#include "rsInstance.hpp"
#include "rsQueue.hpp"
#include <cstdint>

namespace RS{
    void rsInstance::PickPhysicalDevice(){
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance,&physicalDeviceCount, nullptr);

        std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
        vkEnumeratePhysicalDevices(m_Instance,&physicalDeviceCount, physicalDevices.data());

        for(const auto& physicalDevice : physicalDevices){
            if(isDeviceSuitable(physicalDevice)){
                m_PhysicalDevice = physicalDevice;
                break;
            }
        }
        if(m_PhysicalDevice == VK_NULL_HANDLE){
            throw std::runtime_error("Failed to find suitable GPU");
        }
    }

    bool rsInstance::isDeviceSuitable(VkPhysicalDevice physicalDevice){
        rsQueue graphicsQueue;
        QueueFamilyIndices indices = graphicsQueue.FindQueueFamily(physicalDevice);

        VkPhysicalDeviceFeatures deviceFeatures;
        VkPhysicalDeviceProperties deviceProperties;

        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU && indices.isComplete();
    }

    void rsInstance::createLogicalDevice(){
        rsQueue graphicsQueue;

        QueueFamilyIndices indices = graphicsQueue.FindQueueFamily(m_PhysicalDevice);

        float queuePriority = 1.0f;

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
       
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;

        if(enableValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.validationLayers.size());
            createInfo.ppEnabledLayerNames = m_ValidationLayers.validationLayers.data();
        } else{
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &device);
        if(result != VK_SUCCESS){
            throw std::runtime_error("Failed to create logicial device error code: " + std::to_string(result) + "!");
        }
    }
}
