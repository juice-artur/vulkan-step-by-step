#ifndef VULKAN_STEP_BY_STEP_VK_MESH_H
#define VULKAN_STEP_BY_STEP_VK_MESH_H

#include "vk_types.h"
#include "vec3.hpp"
#include <vector>
#include "tiny_obj_loader.h"
#include <iostream>

struct VertexInputDescription {
    std::vector<VkVertexInputBindingDescription> bindings;
    std::vector<VkVertexInputAttributeDescription> attributes;
    VkPipelineVertexInputStateCreateFlags flags = 0;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 uv;

    static VertexInputDescription getVertexDescription();
};

struct Mesh {
    std::vector<Vertex> _vertices;
    AllocatedBuffer _vertexBuffer;
    bool loadFromObj(const char* filename);
};
#endif //VULKAN_STEP_BY_STEP_VK_MESH_H
