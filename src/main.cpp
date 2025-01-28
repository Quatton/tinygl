#include "builder.hpp"
#include "camera_plugin.hpp"
#include "model.hpp"
#include "renderer_plugin.hpp"
#include "shader.hpp"

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
  auto lightModel = cubeModel.copy();
  rd->add_model(ss, cubeModel);
  rd->add_model(ls, lightModel);
  auto cube = Object(glm::vec3(0.0f, 0.0f, 0.0f));
  auto light = Object(glm::vec3(1.2f, 1.0f, 2.0f));
  rd->add_object(cubeModel, cube);
  rd->add_object(lightModel, light);
  rd->set_object_hook(cube, [](ObjectHookInput ctx) {
    ctx.shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    ctx.shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
  });

  app->run();

  return 0;
}
