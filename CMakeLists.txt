cmake_minimum_required(VERSION 3.7.1)

set(PROJECT_NAME "vulkan-step-by-step")
# AUTO_LOCATE_VULKAN - accepted value ON or OFF
# ON  - Use CMake to auto locate the Vulkan SDK.
# OFF - Vulkan SDK path can be specified manually. This is helpful to test the build on various Vulkan version.
option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if(AUTO_LOCATE_VULKAN)
    message(STATUS "Attempting auto locate Vulkan using CMake......")

    # Find Vulkan Path using CMake's Vulkan Module
    # This will return Boolean 'Vulkan_FOUND' indicating the status of find as success(ON) or fail(OFF).
    # Include directory path - 'Vulkan_INCLUDE_DIRS' and 'Vulkan_LIBRARY' with required libraries.
    find_package(Vulkan)

    # Try extracting VulkanSDK path from ${Vulkan_INCLUDE_DIRS}
    if (NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
        set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
        STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
    endif()

    if(NOT Vulkan_FOUND)
        # CMake may fail to locate the libraries but could be able to
        # provide some path in Vulkan SDK include directory variable
        # 'Vulkan_INCLUDE_DIRS', try to extract path from this.
        message(STATUS "Failed to locate Vulkan SDK, retrying again...")
        if(EXISTS "${VULKAN_PATH}")
            message(STATUS "Successfully located the Vulkan SDK: ${VULKAN_PATH}")
        else()
            message("Error: Unable to locate Vulkan SDK. Please turn off auto locate option by specifying 'AUTO_LOCATE_VULKAN' as 'OFF'")
            message("and specify manually path using 'VULKAN_SDK' and 'VULKAN_VERSION' variables in the CMakeLists.txt.")
            return()
        endif()
    endif()
else()
    message(STATUS "Attempting to locate Vulkan SDK using manual path......")
    set(VULKAN_SDK "C:/VulkanSDK")
    set(VULKAN_VERSION "1.0.33.0")
    set(VULKAN_PATH "${VULKAN_SDK}/${VULKAN_VERSION}")
    message(STATUS "Using manual specified path: ${VULKAN_PATH}")

    # Check if manual set path exists
    if(NOT EXISTS "${VULKAN_PATH}")
        message("Error: Unable to locate this Vulkan SDK path VULKAN_PATH: ${VULKAN_PATH}, please specify correct path.
		For more information on correct installation process, please refer to subsection 'Getting started with Lunar-G SDK'
		and 'Setting up first project with CMake' in Chapter 3, 'Shaking hands with the device' in this book 'Learning Vulkan', ISBN - 9781786469809.")
        return()
    endif()
endif()

# Specify a suitable project name
project(${PROJECT_NAME})

# Add any required preprocessor definitions here
add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)

# vulkan-1 library for build Vulkan application.
set(VULKAN_LIB_LIST "vulkan-1")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Include Vulkan header files from Vulkan SDK
    include_directories(AFTER ${VULKAN_PATH}/Include)

    # Link directory for vulkan-1
    link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib;)
endif()


# Define directories and the contained folder and files inside.
if(WIN32)
    source_group("include" REGULAR_EXPRESSION "include/*")
    source_group("source" REGULAR_EXPRESSION "source/*")
endif(WIN32)

add_subdirectory(external)
add_subdirectory(external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
# Define include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Gather list of header and source files for compilation
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.*)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# Build project, give it a name and includes list of file to be compiled
add_executable(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES})

# Link the debug and release libraries to the project
target_link_libraries( ${PROJECT_NAME} ${VULKAN_LIB_LIST} vkbootstrap glfw vma glm tinyobjloader stb_image)

# Define project properties
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

file(GLOB_RECURSE GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/shaders/*.vert"
        "${PROJECT_SOURCE_DIR}/shaders/*.comp"
        )

foreach(GLSL ${GLSL_SOURCE_FILES})
    message(STATUS "BUILDING SHADER")
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
    message(STATUS ${GLSL})
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)

