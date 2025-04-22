#include <vulkan/vulkan.hpp>
#include "rsValidationLayers.hpp"

namespace RS{
    class rsInstance{
        public:
            VkDevice device;

            rsInstance(VkInstance& instance);

            void createInstance();

            void PickPhysicalDevice();

            void createLogicalDevice();

        private:
            rsValidationLayers m_ValidationLayers;

            bool enableValidationLayers = false;

            VkInstance m_Instance;

            bool isDeviceSuitable(VkPhysicalDevice physicalDevice);

            VkPhysicalDevice m_PhysicalDevice;
    };
}