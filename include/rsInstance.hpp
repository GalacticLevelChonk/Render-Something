#include <vulkan/vulkan.hpp>
#include "rsValidationLayers.hpp"

namespace RS{
    class rsInstance{
        public:

            rsInstance(VkInstance& instance);

            void createInstance();

            void PickPhysicalDevice();

        private:
            rsValidationLayers m_ValidationLayers;

            VkInstance m_Instance;

            bool isDeviceSuitable(VkPhysicalDevice physicalDevice);

            VkPhysicalDevice m_PhysicalDevice;
    };
}