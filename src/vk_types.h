#ifndef VULKAN_STEP_BY_STEP_VK_TYPES_H
#define VULKAN_STEP_BY_STEP_VK_TYPES_H

#include <vk_mem_alloc.h>
#include <glm.hpp>

struct AllocatedBuffer {
    VkBuffer _buffer;
    VmaAllocation _allocation;
};

struct AllocatedImage {
    VkImage _image;
    VmaAllocation _allocation;
};

struct MeshPushConstants {
    glm::vec4 data;
    glm::mat4 renderMatrix;
};

struct GPUCameraData{
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 viewproj;
};

struct GPUSceneData {
    glm::vec4 fogColor;
    glm::vec4 fogDistances;
    glm::vec4 ambientColor;
    glm::vec4 sunlightDirection;
    glm::vec4 sunlightColor;
};

struct FrameData {
    VkSemaphore _presentSemaphore, _renderSemaphore;
    VkFence _renderFence;

    VkCommandPool _commandPool;
    VkCommandBuffer _mainCommandBuffer;

    AllocatedBuffer cameraBuffer;
    VkDescriptorSet globalDescriptor;

    AllocatedBuffer objectBuffer;
    VkDescriptorSet objectDescriptor;
};

struct UploadContext {
    VkFence _uploadFence;
    VkCommandPool _commandPool;
    VkCommandBuffer _commandBuffer;
};

struct GPUObjectData{
    glm::mat4 modelMatrix;
};

struct Texture {
    AllocatedImage image;
    VkImageView imageView;
};


#endif //VULKAN_STEP_BY_STEP_VK_TYPES_H
