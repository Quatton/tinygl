#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

  void (*inputCallback)(GLFWwindow *);
  void (*eventLoop)();

  void init();
  void run();
};
