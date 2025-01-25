#include "src/glfw_initialization.h"

#include "src/precomp.h"

#include <GLFW/glfw3.h>

namespace veng
{
GlfwInitialization::GlfwInitialization()
{
  if (glfwInit() != GLFW_TRUE) {
    std::exit(EXIT_FAILURE);
  }
}

GlfwInitialization::~GlfwInitialization() { glfwTerminate(); }
}  // namespace veng
