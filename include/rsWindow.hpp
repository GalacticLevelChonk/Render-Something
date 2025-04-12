#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>


namespace RS{
    class rsWindow{
        public:
            void initWindow(GLFWwindow*& window, int WIDTH, int HEIGHT, std::string name);
    };
}