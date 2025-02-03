#pragma once

// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on

#include "camera.hpp"
#include "config.hpp"
#include "pipeline.hpp"
#include "plugin.hpp"
#include <memory>
#include <typeinfo>

void scroll_callback(GLFWwindow *w, double x, double y);

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

struct CameraContext {
public:
  float lastX = SCR_WIDTH / 2.0f;
  float lastY = SCR_HEIGHT / 2.0f;
  bool firstMouse = true;

  std::unique_ptr<Camera> camera =
      std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

  float ratio = 0.1f;
};

class CameraPlugin : public PluginBase {
public:
  std::unique_ptr<CameraContext> ctx = std::make_unique<CameraContext>();

  void setup(Pipeline &p) override {
    auto *gw = p.window->instance;

    glfwSetWindowUserPointer(gw, &p);
    glfwSetInputMode(gw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(gw, mouse_callback);
    glfwSetScrollCallback(gw, scroll_callback);
    glfwSetFramebufferSizeCallback(gw, framebuffer_size_callback);
  }

  void update(Pipeline &p) override {

    auto *camera = p.get_plugin<CameraPlugin>()->ctx->camera.get();
    auto *window = p.window->instance;
    float deltaTime = p.timer.deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      camera->ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      camera->ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      camera->ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      camera->ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS) {
      {
        camera->ProcessKeyboard(UP, deltaTime);
      }
    }
    if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
         glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) &&
        glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS &&
        // I use ctrl + shift + c to screenshot
        glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS) {
      camera->ProcessKeyboard(DOWN, deltaTime);
    }
  }

  [[nodiscard]] const std::type_info &type() const override {
    return typeid(CameraPlugin);
  }
};
