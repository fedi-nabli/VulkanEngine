#pragma once

#include <src/glfw_window.h>

#include <vulkan/vulkan.h>

namespace veng
{
class Graphics final
{
 public:
  Graphics(gsl::not_null<Window*> window);
  ~Graphics();

 private:
  void InitializeVulkan();
  void CreateInstance();
  gsl::span<gsl::czstring> GetSuggestedExtensions();

  VkInstance instance_ = nullptr;
  gsl::not_null<Window*> window_;
};
}  // namespace veng
