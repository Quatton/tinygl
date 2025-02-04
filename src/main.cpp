#include "builder.hpp"
#include "camera_plugin.hpp"
#include "model.hpp"
#include "object.hpp"
#include "renderer_plugin.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "utils.hpp"
#include <GLFW/glfw3.h>
#include <fmt/core.h>
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

  ss.use();
  ss.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
  ss.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
  ss.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
  ss.setFloat("material.shininess", 32.0f);
  ss.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  ss.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

  ss.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
  ss.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
  ss.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
  ss.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

  ss.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
  ss.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
  ss.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
  ss.setFloat("spotLight.constant", 1.0f);
  ss.setFloat("spotLight.linear", 0.09f);
  ss.setFloat("spotLight.quadratic", 0.032f);
  ss.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
  ss.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

  glm::vec3 pointLightPositions[] = {
      glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
      glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

  for (int i = 0; i < 4; i++) {
    ss.setVec3(fmt::format("pointLights[{}].position", i),
               pointLightPositions[i]);
    ss.setFloat(fmt::format("pointLights[{}].constant", i), 1.0f);
    ss.setFloat(fmt::format("pointLights[{}].linear", i), 0.09f);
    ss.setFloat(fmt::format("pointLights[{}].quadratic", i), 0.032f);
    ss.setVec3(fmt::format("pointLights[{}].ambient", i), 0.05f, 0.05f, 0.05f);
    ss.setVec3(fmt::format("pointLights[{}].diffuse", i), 0.8f, 0.8f, 0.8f);
    ss.setVec3(fmt::format("pointLights[{}].specular", i), 1.0f, 1.0f, 1.0f);
  }

  ss.setInt("material.diffuse", 0);
  ss.setInt("material.specular", 1);

  rd->set_shader_hook(ss, [&containerTexture,
                           &containerSpecular](ShaderHookInput ctx) {
    auto *camera = ctx.pipeline.get_plugin<CameraPlugin>()->ctx->camera.get();

    ctx.shader.setVec3("spotLight.position", camera->Position);
    ctx.shader.setVec3("spotLight.direction", camera->Front);

    ctx.shader.setVec3("viewPos", camera->Position);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, containerTexture->ID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, containerSpecular->ID);
  });

  app->run();

  return 0;
}
