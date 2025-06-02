#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>


namespace RS{
    class rsWindow{
        public:
            rsWindow();

            void initWindow(int WIDTH, int HEIGHT, std::string name);

            void createSurface(VkInstance instance, GLFWwindow *window, VkSurfaceKHR &surface);

            GLFWwindow* getWindow(){
                return window;
            }

        private:
            GLFWwindow* window;
    };
}