#include "builder.hpp"
#include "camera_plugin.hpp"
#include "model.hpp"
#include "renderer_plugin.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <glm/geometric.hpp>
#include <memory>

int main() {
  auto app = PipelineBuilder()
                 .add_plugin<CameraPlugin>()
                 .add_plugin<RendererPlugin>()
                 .build();

  auto *rd = app->get_plugin<RendererPlugin>();

  auto ss = Shader("shaders/shader.vert", "shaders/shader.frag");
  Model backpack("backpack/backpack.obj");

  auto containerTexture = TextureLoader()
                              .from_path("textures/container2.png")
                              .set_wrap_s(Wrap::REPEAT)
                              .set_wrap_t(Wrap::REPEAT)
                              .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
                              .set_mag_filter(MagFilter::NEAREST)
                              .load();

  auto containerSpecular = TextureLoader()
                               .from_path("textures/container2_specular.png")
                               .set_wrap_s(Wrap::REPEAT)
                               .set_wrap_t(Wrap::REPEAT)
                               .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
                               .set_mag_filter(MagFilter::NEAREST)
                               .load();

  rd->add_shader(ss);
  rd->add_model(ss, backpack);

  rd->set_model_hook(backpack, [](ModelHookInput ctx) {
    ctx.mat_model = glm::translate(
        ctx.mat_model,
        glm::vec3(
            0.0f, 0.0f,
            0.0f)); // translate it down so it's at the center of the scene
    ctx.mat_model = glm::scale(
        ctx.mat_model,
        glm::vec3(1.0f, 1.0f,
                  1.0f)); // it's a bit too big for our scene, so scale it down
  });

  app->run();

  return 0;
}
