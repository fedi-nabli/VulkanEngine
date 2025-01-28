#include <src/graphics.h>

#include "src/precomp.h"

#include <GLFW/glfw3.h>

namespace veng
{
Graphics::Graphics(gsl::not_null<Window*> window) : window_(window) { InitializeVulkan(); }

Graphics::~Graphics()
{
  if (instance_ != nullptr)
  {
    vkDestroyInstance(instance_, nullptr);
  }
}

void Graphics::InitializeVulkan() { CreateInstance(); }

void Graphics::CreateInstance()
{
  gsl::span<gsl::czstring> suggested_extensions = GetSuggestedInstanceExtensions();

  if (!AreAllExtensionsSupported(suggested_extensions))
  {
    std::exit(EXIT_FAILURE);
  }

  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = nullptr;  // no extensions (custom)
  app_info.pApplicationName = "Vulkan Engine";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "VEng";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_create_info = {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_create_info.pNext = nullptr;
  instance_create_info.pApplicationInfo = &app_info;
  instance_create_info.enabledExtensionCount = suggested_extensions.size();
  instance_create_info.ppEnabledExtensionNames = suggested_extensions.data();
  instance_create_info.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&instance_create_info, nullptr, &instance_);
  if (result != VK_SUCCESS)
  {
    std::exit(EXIT_FAILURE);
  }
}

gsl::span<gsl::czstring> Graphics::GetSuggestedInstanceExtensions()
{
  std::uint32_t glfw_extension_count = 0;
  gsl::czstring* glfw_extensions;

  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  return {glfw_extensions, glfw_extension_count};
}

std::vector<VkExtensionProperties> Graphics::GetSupportedInstanceExtensions()
{
  std::uint32_t count;
  VkResult result = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

  if (result != VK_SUCCESS)
  {
    std::printf("Failed to enumerate instance extension count");
    std::exit(EXIT_FAILURE);
  }

  if (count == 0)
  {
    return {};
  }

  std::vector<VkExtensionProperties> properties(count);
  result = vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
  if (result != VK_SUCCESS)
  {
    std::printf("Failed to enumerate instance extensions");
    std::exit(EXIT_FAILURE);
  }

  return properties;
}

bool Graphics::ExtensionMatchesName(gsl::czstring name, const VkExtensionProperties& properties) { return veng::streq(properties.extensionName, name); }

bool Graphics::IsExtensionSupported(gsl::span<VkExtensionProperties> extensions, gsl::czstring name)
{
  return std::any_of(extensions.begin(), extensions.end(), std::bind_front(ExtensionMatchesName, name));
}

bool Graphics::AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions)
{
  std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();
  return std::all_of(extensions.begin(), extensions.end(), std::bind_front(IsExtensionSupported, supported_extensions));
}
}  // namespace veng
