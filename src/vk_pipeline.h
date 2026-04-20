#ifndef VULKAN_STEP_BY_STEP_VK_PIPELINE_H
#define VULKAN_STEP_BY_STEP_VK_PIPELINE_H

#include <vulkan/vulkan_core.h>
#include <vector>

class PipelineBuilder  {
public:
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    VkPipelineVertexInputStateCreateInfo vertexInputInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineRasterizationStateCreateInfo rasterizer;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineMultisampleStateCreateInfo multisampling;
    VkPipelineLayout pipelineLayout;
    VkPipelineDepthStencilStateCreateInfo depthStencil;
    VkPipeline buildPipeline(VkDevice device, VkRenderPass pass);
};


#endif //VULKAN_STEP_BY_STEP_VK_PIPELINE_H
