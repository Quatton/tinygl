#include "app.hpp"
#include "config.hpp"
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  AppBuilder config;
  config.setWindowSize(SCR_WIDTH, SCR_HEIGHT);
  config.setOpenGLVersion(3, 3);
  config.setWindowName("LearnOpenGL");

  App app = config.build();

  app.init();

  app.run();

  return 0;
}