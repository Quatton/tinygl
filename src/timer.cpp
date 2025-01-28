#include "timer.hpp"
#include "GLFW/glfw3.h"

void Timer::tick() {
  auto currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
}