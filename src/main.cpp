#include "config.hpp"

#include <glm/fwd.hpp>
#include <iostream>

const glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

int main() {
  auto app = AppBuilder()
                 .setWindowSize(SCR_WIDTH, SCR_HEIGHT)
                 .setOpenGLVersion(3, 3)
                 .setWindowName("LearnOpenGL")
                 .build();

  for (int i = 0; i < 10; i++) {
    app->spawn(
        CubeObject(cubePositions[i],
                   (glm::quat)glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                                          glm::radians(20.0f * i),
                                          glm::vec3(1.0f, 0.3f, 0.5f))));
  }

  app->insert_texture(*TextureLoader()
                           .from_path("textures/container.jpg")
                           .set_wrap_s(Wrap::REPEAT)
                           .set_wrap_t(Wrap::REPEAT)
                           .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
                           .set_mag_filter(MagFilter::NEAREST)
                           .set_flip_vertically(true)
                           .load());

  app->insert_texture(*TextureLoader()
                           .from_path("textures/awesomeface.png")
                           .set_wrap_s(Wrap::REPEAT)
                           .set_wrap_t(Wrap::REPEAT)
                           .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
                           .set_mag_filter(MagFilter::NEAREST)
                           .set_flip_vertically(true)
                           .set_alpha_channel(true)
                           .load());

  app->run();

  return 0;
}