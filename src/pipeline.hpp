#pragma once

#include <glad/glad.h>

#include "plugin.hpp"
#include "timer.hpp"
#include "window.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Pipeline {
public:
  std::unique_ptr<Window> window;
  Timer timer;

  void run() {
    auto *gw = window->instance;

    glUseProgram(3);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL Error: " << error << std::endl;
      throw;
    }

    while (!glfwWindowShouldClose(gw)) {
      timer.tick();

      window->clear();

      update();

      glfwSwapBuffers(gw);
      glfwPollEvents();
    }
  }

  void setup() {
    for (auto &plugin : plugins_) {
      plugin->setup(*this);
    }
  }

  void update() {
    for (auto &plugin : plugins_) {
      plugin->update(*this);
    }
  }

  template <typename T> T *get_plugin() {
    for (auto &plugin : plugins_) {
      if (plugin->type() == typeid(T)) {
        return static_cast<T *>(plugin.get());
      }
    }
    return nullptr;
  }

  Pipeline(std::unique_ptr<Window> window) : window(std::move(window)) {}

  friend class PipelineBuilder;

private:
  std::vector<std::unique_ptr<PluginBase>> plugins_;
};