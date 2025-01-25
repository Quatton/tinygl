#pragma once

#include "camera.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class App {
public:
  App();
  ~App();
  GLFWwindow *window;

  int majorVersion;
  int minorVersion;

  int windowWidth;
  int windowHeight;

  const char *windowName;

  unsigned int VBO, VAO, EBO;

  void init();
  void run();
};
