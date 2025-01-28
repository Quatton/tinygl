#pragma once

#include "camera_plugin.hpp"
#include "model.hpp"
#include "object.hpp"
#include "pipeline.hpp"
#include "plugin.hpp"
#include "res.hpp"
#include "shader.hpp"
#include <functional>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <map>
#include <optional>

struct ObjectHookInput {
  Pipeline &pipeline;
  Shader &shader;
  Model &model;
  Object &object;
  glm::mat4 &mat_model;
};

struct RendererContext {
  std::map<unsigned int, std::reference_wrapper<Shader>> shaders;
  std::map<unsigned int, std::vector<std::reference_wrapper<Model>>>
      shader_models;
  std::map<unsigned int, std::vector<std::reference_wrapper<Object>>>
      model_objects;
  std::map<unsigned int, std::vector<std::function<void(ObjectHookInput)>>>
      object_hooks;
};

class RendererPlugin : public PluginBase {
public:
  std::unique_ptr<RendererContext> ctx = std::make_unique<RendererContext>();

  RendererPlugin() = default;

  void add_shader(Shader &s) const {
    ctx->shaders.emplace(s.ID, std::ref(s));
    ctx->shader_models.emplace(s.ID,
                               std::vector<std::reference_wrapper<Model>>());
  }

  void add_model(Shader &s, Model &m) const {
    m.ID = ctx->model_objects.size();

    ctx->model_objects.emplace(m.ID,
                               std::vector<std::reference_wrapper<Object>>());
    auto f = ctx->shader_models.find(s.ID);
    if (f == ctx->shader_models.end()) {
      throw std::runtime_error(
          "Cannot add model to shader that's not registered with a shader");
    }

    f->second.emplace_back(m);
  }

  void add_object(Model &m, Object &o) const {
    o.ID = ctx->object_hooks.size();
    ctx->object_hooks.emplace(
        o.ID, std::vector<std::function<void(ObjectHookInput)>>());
    auto f = ctx->model_objects.find(m.ID);
    if (f == ctx->model_objects.end()) {
      throw std::runtime_error(
          "Cannot add object to model that's not registered with a shader");
    }

    f->second.emplace_back(o);
  }

  void set_object_hook(Object &o, void (*hook)(ObjectHookInput)) const {
    auto f = ctx->object_hooks.find(o.ID);
    if (f == ctx->object_hooks.end()) {
      throw std::runtime_error(
          "Cannot set hook for object that's not registered");
    }

    f->second.emplace_back(hook);
  }

  void setup([[maybe_unused]] Pipeline &p) override {}

  void update(Pipeline &p) override {
    auto *camera = p.get_plugin<CameraPlugin>()->ctx->camera.get();
    auto *window = p.window.get();
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(camera->Zoom),
        (float)window->width / (float)window->height, 0.1f, 100.0f);

    for (auto [sID, s] : ctx->shaders) {
      s.get().use();
      s.get().setMat4("projection", projection);
      s.get().setMat4("view", view);

      for (auto r_m : ctx->shader_models[sID]) {
        for (auto r_o : ctx->model_objects[r_m.get().ID]) {
          auto obj = r_o.get();

          auto model = glm::mat4(1.0f);
          model = glm::translate(model, obj.position);
          model = model * glm::mat4_cast(obj.rotation);

          for (const auto &hook : ctx->object_hooks[obj.ID]) {
            hook(ObjectHookInput{p, s, r_m.get(), obj, model});
          }

          s.get().setMat4("model", model);

          r_m.get().draw();
        }
      }
    }
  }

  [[nodiscard]] const std::type_info &type() const override {
    return typeid(RendererPlugin);
  }
};