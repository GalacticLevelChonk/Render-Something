#include <vulkan/vulkan.hpp>
#include "rsValidationLayers.hpp"

namespace RS{
    class rsInstance{
        public:
            VkDevice device;

            rsInstance(VkInstance& instance);

            void createInstance(VkInstance &instance);

            void PickPhysicalDevice(VkInstance instance);

            void createLogicalDevice();

        private:
            rsValidationLayers m_ValidationLayers;

            bool enableValidationLayers = false;

            bool isDeviceSuitable(VkPhysicalDevice physicalDevice);

            VkPhysicalDevice m_PhysicalDevice;
    };
}