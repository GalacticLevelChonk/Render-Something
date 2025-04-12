#include "rsWindow.hpp"

namespace RS{
    void rsWindow::initWindow(GLFWwindow*& window, int WIDTH, int HEIGHT, std::string name){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, name.c_str(), nullptr, nullptr);
    }
}