#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "rsWindow.hpp"
#include "rsInstance.hpp"

namespace RS{
    class rsApp{
        public:
            void run();

        private:
            void initVulkan();
            void mainLoop();
            void cleanup();

            GLFWwindow* window;
            rsWindow appWindow;
            VkSurfaceKHR surface;

            VkInstance instance;
            rsInstance appInstance{instance};
    };
}