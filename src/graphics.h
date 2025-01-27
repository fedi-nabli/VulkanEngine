#pragma once

#include <src/glfw_window.h>

#include <vector>

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
  static gsl::span<gsl::czstring> GetSuggestedInstanceExtensions();
  static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();

  VkInstance instance_ = nullptr;
  gsl::not_null<Window*> window_;
};
}  // namespace veng
