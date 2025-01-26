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
  AppBuilder config;
  config.setWindowSize(SCR_WIDTH, SCR_HEIGHT);
  config.setOpenGLVersion(3, 3);
  config.setWindowName("LearnOpenGL");

  App *app = config.build();

  for (int i = 0; i < 10; i++) {
    app->spawn(
        CubeObject(cubePositions[i],
                   (glm::quat)glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
                                          glm::radians(20.0f * i),
                                          glm::vec3(1.0f, 0.3f, 0.5f))));
  }

  app->run();

  return 0;
}