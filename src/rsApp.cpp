#include "rsApp.hpp"

namespace RS{
    void rsApp::run(){
        appWindow.initWindow(window, 1000, 800, "Vulkan");
        initVulkan();
        mainLoop();
        cleanup();
    }

    void rsApp::initVulkan(){
        appInstance.createInstance(instance);
        appWindow.createSurface(instance, window,surface);
        appInstance.PickPhysicalDevice(instance, surface);
        appInstance.createLogicalDevice(surface);
    }

    void rsApp::mainLoop(){
        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();
        }
    }

    void rsApp::cleanup(){
        glfwDestroyWindow(window);

        glfwTerminate();

        vkDestroySurfaceKHR(instance, surface, nullptr);

        vkDestroyDevice(appInstance.device, nullptr);

        vkDestroyInstance(instance, nullptr);
    }
}