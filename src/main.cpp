#include "builder.hpp"
#include "camera_plugin.hpp"
#include "model.hpp"
#include "object.hpp"
#include "renderer_plugin.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <memory>

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

int main() {
  auto app = PipelineBuilder()
                 .add_plugin<CameraPlugin>()
                 .add_plugin<RendererPlugin>()
                 .build();

  auto *rd = app->get_plugin<RendererPlugin>();
  auto ss = Shader("shaders/shader.vert", "shaders/shader.frag");

  rd->add_shader(ss);

  auto cubeModel = CubeModel::create();
  rd->add_model(ss, cubeModel);

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

  auto cubes = std::vector<std::unique_ptr<Object>>();

  for (auto i = 0; i < 10; i++) {
    auto cube = std::make_unique<Object>();
    cube->model = cubeModel;
    cube->position = cubePositions[i];
    cubes.push_back(std::move(cube));

    rd->add_object(cubeModel, *cubes[i]);
  }

  rd->set_shader_hook(
      ss, [&containerTexture, &containerSpecular](ShaderHookInput ctx) {
        auto t = glfwGetTime();
        auto lightDir = glm::normalize(glm::vec3(sin(t), -1.0f, cos(t)));

        ctx.shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        ctx.shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        ctx.shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        ctx.shader.setFloat("material.shininess", 32.0f);
        ctx.shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ctx.shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ctx.shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        ctx.shader.setVec3("light.diffuse", 0.5f, 0.5f,
                           0.5f); // darken diffuse light a bit
        ctx.shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        ctx.shader.setVec3(
            "viewPos",
            ctx.pipeline.get_plugin<CameraPlugin>()->ctx->camera->Position);

        ctx.shader.setInt("material.diffuse", 0);
        ctx.shader.setInt("material.specular", 1);
        ctx.shader.setVec3("light.direction", lightDir);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture->ID);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, containerSpecular->ID);
      });

  app->run();

  return 0;
}
