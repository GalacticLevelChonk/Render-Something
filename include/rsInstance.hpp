#include <vulkan/vulkan.hpp>
#include "rsValidationLayers.hpp"

namespace RS{
    class rsInstance{
        public:
            VkDevice device;

            VkQueue presentQueue;

            rsInstance(VkInstance& instance);

            void createInstance(VkInstance &instance);

            void PickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);

            void createLogicalDevice(VkSurfaceKHR surface);

        private:
            rsValidationLayers m_ValidationLayers;

            bool enableValidationLayers = false;

            bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

            VkPhysicalDevice m_PhysicalDevice;
    };
}