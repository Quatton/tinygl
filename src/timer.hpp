#pragma once

#include <GLFW/glfw3.h>

class Timer {
public:
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  void tick() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
  }
};