cmake_minimum_required(VERSION 3.22...3.29)
cmake_policy(VERSION 3.22)
set(CMAKE_POLICY_VERSION_MINIMUM 3.22)

project(VulkanEngine)

find_package(Vulkan REQUIRED)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  glm
  GIT_REPOSITORY "https://github.com/g-truc/glm.git"
  GIT_TAG "0.9.9.8"
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(glm)

set(GLFW_BUILD_DOCS OFF)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw.git"
  GIT_TAG "3.3.8"
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
  microsof-gsl
  GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
  GIT_TAG "v4.0.0"
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(microsof-gsl)

file(GLOB_RECURSE VulkanEngineSources CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h"
)

add_executable(VulkanEngine ${VulkanEngineSources})

target_link_libraries(VulkanEngine PRIVATE Vulkan::Vulkan)
target_link_libraries(VulkanEngine PRIVATE glm)
target_link_libraries(VulkanEngine PRIVATE glfw)
target_link_libraries(VulkanEngine PRIVATE Microsoft.GSL::GSL)

target_include_directories(VulkanEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/includes")
target_compile_features(VulkanEngine PRIVATE cxx_std_20)
