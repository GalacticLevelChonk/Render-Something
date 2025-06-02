#include <vulkan/vulkan.hpp>
#include "rsValidationLayers.hpp"

namespace RS{
    class rsInstance{
        public:
            VkDevice device;

            VkPhysicalDevice physicalDevice;

            VkQueue presentQueue;

            rsInstance(VkInstance& instance);

            void createInstance(VkInstance &instance);

            void pickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

            void createLogicalDevice(VkSurfaceKHR surface);

        private:
            bool m_extensionSupport;

            rsValidationLayers m_ValidationLayers;

            const std::vector<const char*> m_DeviceFeatures = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            bool enableValidationLayers = false;

            bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    };
}