#include "VulkanEngine.h"
int main(){
    VulkanEngine vulkanEngine{};
    vulkanEngine.init();
    vulkanEngine.run();
    vulkanEngine.cleanup();
    return 0;
};