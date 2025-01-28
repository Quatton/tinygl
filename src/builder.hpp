#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
// clang-format on

#include "config.hpp"
#include "pipeline.hpp"
#include "window.hpp"

class PipelineBuilder {
public:
  int windowWidth = SCR_WIDTH;
  int windowHeight = SCR_HEIGHT;
  int majorVersion = 3;
  int minorVersion = 3;
  const char *windowName = "LearnOpenGL";

  PipelineBuilder() = default;
  ~PipelineBuilder() = default;

  template <typename Plugin, typename... Args>
  PipelineBuilder &add_plugin(Args &&...args) {
    plugins_.emplace_back(
        std::make_unique<Plugin>(std::forward<Args>(args)...));
    return *this;
  }

  PipelineBuilder &size(int width, int height) {

    windowWidth = width;
    windowHeight = height;
    return *this;
  }

  PipelineBuilder &glVersion(int major, int minor) {
    majorVersion = major;
    minorVersion = minor;
    return *this;
  }

  PipelineBuilder &name(const char *name) {
    windowName = name;
    return *this;
  }

  std::unique_ptr<Pipeline> build() {
    auto pipeline = std::make_unique<Pipeline>(std::make_unique<Window>(
        majorVersion, minorVersion, windowName, windowWidth, windowHeight));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      throw;
    }

    glEnable(GL_DEPTH_TEST);

    auto *instance = pipeline->window->instance;

    glfwSetWindowUserPointer(instance, &pipeline);
    pipeline->plugins_ = std::move(plugins_);
    pipeline->setup();

    return pipeline;
  }

private:
  std::vector<std::unique_ptr<PluginBase>> plugins_;
};