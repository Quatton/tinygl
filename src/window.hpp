#pragma once

// clang-format off
#include <GLFW/glfw3.h>
// clang-format on

#include "config.hpp"

#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

class Window {
public:
  int width = SCR_WIDTH;
  int height = SCR_HEIGHT;

  glm::vec4 clearColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);

  GLFWwindow *instance;

  ~Window() {
    glfwDestroyWindow(instance);
    glfwTerminate();
  }

  void clear() const {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  Window(int majorVersion, int minorVersion, const char *windowName, int width,
         int height) {
    this->width = width;
    this->height = height;

    if (!glfwInit()) {
      throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS
#endif

    instance = glfwCreateWindow(width, height, windowName, nullptr, nullptr);
    if (!instance) {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(instance);
  }
};
