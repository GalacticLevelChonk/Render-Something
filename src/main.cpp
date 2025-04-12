#include "rsApp.hpp"

#include <iostream>
#include <exception>
#include <cstdlib>


using namespace RS;

int main(){
    rsApp app;

    try{
        app.run();
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}