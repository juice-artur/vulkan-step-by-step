#ifndef VULKAN_STEP_BY_STEP_VK_TYPES_H
#define VULKAN_STEP_BY_STEP_VK_TYPES_H

#include <vk_mem_alloc.h>
#include <glm.hpp>

struct AllocatedBuffer {
    VkBuffer _buffer;
    VmaAllocation _allocation;
};

struct MeshPushConstants {
    glm::vec4 data;
    glm::mat4 renderMatrix;
};

#endif //VULKAN_STEP_BY_STEP_VK_TYPES_H
