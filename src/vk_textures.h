#pragma once

#include "vk_types.h"
#include "VulkanEngine.h"

namespace vkutil {

    bool loadImageFromFile(VulkanEngine &engine, const char *file, AllocatedImage &outImage);

}