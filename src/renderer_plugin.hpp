#pragma once

#include "camera_plugin.hpp"
#include "model.hpp"
#include "pipeline.hpp"
#include "plugin.hpp"
#include "shader.hpp"
#include <functional>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <optional>

struct ModelHookInput {
  Pipeline &pipeline;
  Shader &shader;
  Model &model;
  glm::mat4 &mat_model;
};

struct ShaderHookInput {
  Pipeline &pipeline;
  Shader &shader;
};

struct RendererContext {
  std::map<unsigned int, std::reference_wrapper<Shader>> shaders;
  std::map<unsigned int, std::vector<std::reference_wrapper<Model>>>
      shader_models;
  std::map<unsigned int, std::vector<std::function<void(ShaderHookInput)>>>
      shader_hooks;
  std::map<unsigned int, std::vector<std::function<void(ModelHookInput)>>>
      model_hooks;
};

class RendererPlugin : public PluginBase {
public:
  std::unique_ptr<RendererContext> ctx = std::make_unique<RendererContext>();

  RendererPlugin() = default;

  void add_shader(Shader &s) const {
    ctx->shaders.emplace(s.ID, std::ref(s));
    ctx->shader_models.emplace(s.ID,
                               std::vector<std::reference_wrapper<Model>>());
    ctx->shader_hooks.emplace(
        s.ID, std::vector<std::function<void(ShaderHookInput)>>());
  }

  void add_model(Shader &s, Model &m) const {
    m.ID = ctx->model_hooks.size();
    ctx->model_hooks.emplace(
        m.ID, std::vector<std::function<void(ModelHookInput)>>());
    auto f = ctx->shader_models.find(s.ID);
    if (f == ctx->shader_models.end()) {
      throw std::runtime_error(
          "Cannot add model to shader that's not registered with a shader");
    }

    f->second.emplace_back(m);
  }

  void set_model_hook(Model &m,
                      std::function<void(ModelHookInput)> hook) const {
    auto f = ctx->model_hooks.find(m.ID);
    if (f == ctx->model_hooks.end()) {
      throw std::runtime_error(
          "Cannot set hook for object that's not registered");
    }

    f->second.emplace_back(hook);
  }

  void set_shader_hook(Shader &s,
                       std::function<void(ShaderHookInput)> hook) const {
    auto f = ctx->shader_hooks.find(s.ID);
    if (f == ctx->shader_hooks.end()) {
      throw std::runtime_error(
          "Cannot set hook for shader that's not registered");
    }

    f->second.emplace_back(hook);
  }

  void setup([[maybe_unused]] Pipeline &p) override {}

  void update(Pipeline &p) override {
    auto *camera = p.get_plugin<CameraPlugin>()->ctx->camera.get();
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    for (auto [sID, s] : ctx->shaders) {
      s.get().use();
      s.get().setMat4("projection", projection);
      s.get().setMat4("view", view);

      for (const auto &hook : ctx->shader_hooks[s.get().ID]) {
        hook(ShaderHookInput{p, s.get()});
      }

      for (auto r_m : ctx->shader_models[sID]) {
        auto m = r_m.get();
        auto model = glm::mat4(1.0f);

        for (const auto &hook : ctx->model_hooks[m.ID]) {
          hook(ModelHookInput{p, s.get(), r_m.get(), model});
        }

        s.get().setMat4("model", model);

        r_m.get().Draw(s);
      }
    }
  }

  [[nodiscard]] const std::type_info &type() const override {
    return typeid(RendererPlugin);
  }
};