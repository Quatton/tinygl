#include "builder.hpp"
#include "camera_plugin.hpp"
#include "model.hpp"
#include "renderer_plugin.hpp"
#include "shader.hpp"
#include <GLFW/glfw3.h>

int main() {
  auto app = PipelineBuilder()
                 .add_plugin<CameraPlugin>()
                 .add_plugin<RendererPlugin>()
                 .build();

  auto *rd = app->get_plugin<RendererPlugin>();
  auto ss = Shader("shaders/shader.vert", "shaders/shader.frag");
  auto ls = Shader("shaders/light.vert", "shaders/light.frag");

  rd->add_shader(ss);
  rd->add_shader(ls);

  auto cubeModel = CubeModel::create();
  rd->add_model(ss, cubeModel);
  auto lightModel = cubeModel.copy();
  rd->add_model(ls, lightModel);

  auto cube = Object(glm::vec3(0.0f, 0.0f, 0.0f));
  rd->add_object(cubeModel, cube);

  auto lightPos = glm::vec3(0.0f, 1.0f, 1.0f);
  auto light = Object(lightPos);
  rd->add_object(lightModel, light);

  rd->set_object_hook(cube, [](ObjectHookInput ctx) {
    auto t = glfwGetTime();
    auto lightPos = glm::vec3(sin(t), 1.0f, cos(t)) * 2.0f;
    ctx.shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    ctx.shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    ctx.shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    ctx.shader.setFloat("material.shininess", 32.0f);
    ctx.shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    ctx.shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    ctx.shader.setVec3("lightPos", lightPos);
    ctx.shader.setVec3(
        "viewPos",
        ctx.pipeline.get_plugin<CameraPlugin>()->ctx->camera->Position);
  });

  rd->set_object_hook(light, [](ObjectHookInput ctx) {
    auto t = glfwGetTime();
    ctx.object.position = glm::vec3(sin(t), 1.0f, cos(t)) * 2.0f;
  });

  app->run();

  return 0;
}
