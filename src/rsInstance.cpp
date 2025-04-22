#include "rsInstance.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <stdexcept>

namespace RS{
    rsInstance::rsInstance(VkInstance& instance) : m_Instance(instance){
        createInstance();
    }

    void rsInstance::createInstance(){
        #ifdef NDEBUG
            enableValidationLayers = false;
        #else
            enableValidationLayers = true;
        #endif
            
        if(enableValidationLayers && !m_ValidationLayers.CheckValidationSupport()){
            throw std::runtime_error("Validation layers requested but not available");
        } 

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "RS Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> requiredExtensions;

        for(int i = 0; i < glfwExtensionCount; i++){
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }

        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        if(enableValidationLayers){
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = m_ValidationLayers.validationLayers.data();
        } else{
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
        if(result != VK_SUCCESS){
            throw std::runtime_error("Failed to create instance error code: " + std::to_string(result) + "!");
        }
    }
}