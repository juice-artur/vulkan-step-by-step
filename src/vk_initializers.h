#ifndef VULKAN_STEP_BY_STEP_VK_INITIALIZERS_H
#define VULKAN_STEP_BY_STEP_VK_INITIALIZERS_H


#include <vulkan/vulkan_core.h>

namespace vkinit {

    VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags = 0);

    VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t count = 1,
                                                          VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    VkPipelineShaderStageCreateInfo
    pipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule);

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo();

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo(VkPrimitiveTopology topology);

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo(VkPolygonMode polygonMode);

    VkPipelineMultisampleStateCreateInfo multisamplingStateCreateInfo();

    VkPipelineColorBlendAttachmentState colorBlendAttachmentState();

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo();

    VkFenceCreateInfo fenceCreateInfo(VkFenceCreateFlags flags = 0);

    VkSemaphoreCreateInfo semaphoreCreateInfo(VkSemaphoreCreateFlags flags = 0);

    VkImageCreateInfo imageCreateInfo(VkFormat format, VkImageUsageFlags usageFlags, VkExtent3D extent);

    VkImageViewCreateInfo imageviewCreateInfo(VkFormat format, VkImage image, VkImageAspectFlags aspectFlags);

    VkPipelineDepthStencilStateCreateInfo
    depthStencilCreateInfo(bool bDepthTest, bool bDepthWrite, VkCompareOp compareOp);

    VkWriteDescriptorSet
    writeDescriptorBuffer(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo *bufferInfo,
                          uint32_t binding);

    VkDescriptorSetLayoutBinding
    descriptorSetLayoutBinding(VkDescriptorType type, VkShaderStageFlags stageFlags, uint32_t binding);

    VkCommandBufferBeginInfo commandBufferBeginInfo(VkCommandBufferUsageFlags flags = 0);

    VkSubmitInfo submitInfo(VkCommandBuffer *cmd);

    VkSamplerCreateInfo samplerCreateInfo(VkFilter filters, VkSamplerAddressMode samplerAddressMode = VK_SAMPLER_ADDRESS_MODE_REPEAT);

    VkWriteDescriptorSet writeDescriptorImage(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorImageInfo *imageInfo,
                         uint32_t binding);
}

#endif //VULKAN_STEP_BY_STEP_VK_INITIALIZERS_H
