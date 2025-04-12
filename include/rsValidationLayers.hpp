#include <vector>


namespace RS{
    class rsValidationLayers{
        public:
            bool CheckValidationSupport();
           
            const std::vector<const char*> validationLayers{
                "VK_LAYER_KHRONOS_validation"
            };
    };
}