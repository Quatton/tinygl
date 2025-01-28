#pragma once

#include "context.hpp"
#include "plugin.hpp"
#include <map>
#include <memory>
#include <vector>

class Pipeline {
public:
  std::unique_ptr<PipelineContext> ctx;

  void run() {
    auto *gw = ctx->window->instance;
    while (!glfwWindowShouldClose(gw)) {
      ctx->timer->tick();
      ctx->window->clear();

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

  Pipeline(std::unique_ptr<PipelineContext> ctx) : ctx(std::move(ctx)) {}

private:
  // void render();

  std::vector<std::unique_ptr<PluginBase>> plugins_;
};