#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "camera.hpp"
#include "config.hpp"
#include "pipeline.hpp"
#include "plugin.hpp"
#include <typeinfo>

void scroll_callback(GLFWwindow *w, double x, double y);

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods);

class CameraContext {
public:
  float lastX = SCR_WIDTH / 2.0f;
  float lastY = SCR_HEIGHT / 2.0f;
  bool firstMouse = true;

  Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

  float ratio = 0.1f;
};

class CameraPlugin : public PluginBase {
public:
  CameraContext ctx;
  void setup(Pipeline &p) override {
    auto *window = p.ctx->window->instance;

    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
  }

  [[nodiscard]] const std::type_info &type() const override {
    return typeid(CameraPlugin);
  }
};