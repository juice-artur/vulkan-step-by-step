add_library(vma INTERFACE)
add_library(glm INTERFACE)
add_library(stb_image INTERFACE)
add_library(tinyobjloader STATIC)

add_library(vkbootstrap STATIC)
target_sources(vkbootstrap PRIVATE 
  vkbootstrap/VkBootstrap.h
  vkbootstrap/VkBootstrap.cpp
  )
target_include_directories(vkbootstrap PUBLIC vkbootstrap)

target_sources(tinyobjloader PRIVATE
        tinyobjloader/tiny_obj_loader.h
        tinyobjloader/tiny_obj_loader.cc
        )

target_include_directories(tinyobjloader PUBLIC tinyobjloader)
target_include_directories(vma INTERFACE vma)
target_include_directories(glm INTERFACE glm)
target_include_directories(stb_image INTERFACE stb_image)