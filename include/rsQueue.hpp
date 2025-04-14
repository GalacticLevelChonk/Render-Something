#include <cstdint>
#include <optional>
#include <vulkan/vulkan.hpp>

namespace RS{
    struct QueueFamilyIndices{
        std::optional<uint32_t> graphicsFamily;

        bool isComplete();
    };

    class rsQueue{
        public:
            QueueFamilyIndices FindQueueFamily(VkPhysicalDevice device);
    };
}