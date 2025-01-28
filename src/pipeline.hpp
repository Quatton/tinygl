#pragma once

#include "context.hpp"
#include "plugin.hpp"
#include <map>
#include <memory>
#include <vector>

class Pipeline {
public:
  std::unique_ptr<Window> window;
  Timer timer;

  void run() {
    auto *gw = window->instance;
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

private:
  // void render();

  std::vector<std::unique_ptr<PluginBase>> plugins_;
};