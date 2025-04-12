#include "rsValidationLayers.hpp"
#include <cstring>
#include <vulkan/vulkan.hpp>

namespace RS{
    bool rsValidationLayers::CheckValidationSupport(){
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for(const char* layerName : validationLayers){
            bool layerFound = false;

             for(const auto& layerProperty : availableLayers){
                if(strcmp(layerName, layerProperty.layerName) == 0){
                    layerFound = true;
                    break;
                }
             }
             
             if(!layerFound){
                return false;
             }
        }
    return true;
    }
}