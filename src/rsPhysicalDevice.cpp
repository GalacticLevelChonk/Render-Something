#include "rsInstance.hpp"
#include "rsQueue.hpp"

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
}
