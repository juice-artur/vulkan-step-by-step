#ifndef VULKAN_STEP_BY_STEP_VULKANENGINE_H
#define VULKAN_STEP_BY_STEP_VULKANENGINE_H

#include <vulkan/vulkan.h>
#include <unordered_map>
#include "vector"
#include "GLFW/glfw3.h"
#include "VkBootstrap.h"
#include "deletion_queue.h"
#include "vk_types.h"
#include "vk_mesh.h"

struct Material {
    VkDescriptorSet textureSet{VK_NULL_HANDLE};
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
};

struct RenderObject {
    Mesh *mesh;
    Material *material;
    glm::mat4 transformMatrix;
};
constexpr unsigned int FRAME_OVERLAP = 2;

class VulkanEngine {
public:

    void init();

    void run();

    void cleanup();

    void immediateSubmit(std::function<void(VkCommandBuffer cmd)>&& function);

    AllocatedBuffer createBuffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);

    VmaAllocator _allocator;

    deletion_queue _mainDeletionQueue;

private:
    VkExtent2D _windowExtent{800, 600};

    UploadContext _uploadContext;

    GLFWwindow *_window;
    VkInstance _instance;
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkPhysicalDevice _chosenGPU;
    VkDevice _device;
    VkSurfaceKHR _surface;

    VkPhysicalDeviceProperties _gpuProperties;

    VkSwapchainKHR _swapchain;
    VkFormat _swapchainImageFormat;
    std::vector<VkImage> _swapchainImages;
    std::vector<VkImageView> _swapchainImageViews;

    VkQueue _graphicsQueue;
    uint32_t _graphicsQueueFamily;

    FrameData _frames[FRAME_OVERLAP];

    VkRenderPass _renderPass;
    std::vector<VkFramebuffer> _frameBuffers;

    VkImageView _depthImageView;
    AllocatedImage _depthImage;
    VkFormat _depthFormat;

    VkDescriptorSetLayout _globalSetLayout;
    VkDescriptorSetLayout _objectSetLayout;
    VkDescriptorSetLayout _singleTextureSetLayout;
    VkDescriptorPool _descriptorPool;

    GPUSceneData _sceneParameters;
    AllocatedBuffer _sceneParameterBuffer;

    std::vector<RenderObject> _renderables;
    std::unordered_map<std::string, Material> _materials;
    std::unordered_map<std::string, Mesh> _meshes;

    std::unordered_map<std::string, Texture> _loadedTextures;

    int _frameNumber = 0;

    glm::vec3 _cameraPos = glm::vec3(0.f, -6.f, -10.f);
    glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

    float _deltaTime = 0.0f;
    float _lastFrame = 0.0f;

    float _lastX = _windowExtent.width / 2.0;
    float _lastY = _windowExtent.height / 2.0;

    float _yaw = -90.0f;
    float _pitch = 0.0f;
    float _sensitivity = 0.05;

    void initWindow();

    void initVulkan();

    void initSwapchain();

    void initCommands();

    void initDefaultRenderPass();

    void initFrameBuffers();

    void initSyncStructures();

    void initPipelines();

    void draw();

    bool loadShaderModule(const char *filePath, VkShaderModule *outShaderModule);

    void loadMeshes();

    void uploadMesh(Mesh &mesh);

    void drawObjects(VkCommandBuffer cmd, RenderObject *first, int count);

    void initScene();

    void processInput(GLFWwindow *window);

    void mouseMovement(GLFWwindow *window);

    void calculationDirection();

    void initDescriptors();

    void loadImages();

    Material *createMaterial(VkPipeline pipeline, VkPipelineLayout layout, const std::string &name);

    Material *getMaterial(const std::string &name);

    Mesh *getMesh(const std::string &name);

    FrameData& getCurrentFrame();

    size_t padUniformBufferSize(size_t originalSize);
};


#endif
