#include "rsWindow.hpp"
#include <stdexcept>

namespace RS{
    void rsWindow::initWindow(GLFWwindow*& window, int WIDTH, int HEIGHT, std::string name){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr);
    }

    void rsWindow::createSurface(VkInstance instance, GLFWwindow *window ,VkSurfaceKHR &surface){
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
}