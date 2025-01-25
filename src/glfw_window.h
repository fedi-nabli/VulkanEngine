#pragma once

struct GLFWwindow;

namespace veng
{
class Window
{
 public:
  Window(gsl::czstring name, glm::ivec2 size);
  ~Window();

  glm::ivec2 GetWindowSize() const;
  bool ShouldClose() const;
  GLFWwindow* GetHandle() const;

  // If you have more than one screen, you can change 0 to the number of the screen - 1 (0 is the primary screen, 1 is the secondary...)
  bool TryMoveToMonitor(std::uint16_t monitor_number);

 private:
  GLFWwindow* window_;
};
}  // namespace veng
