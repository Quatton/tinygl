#include <GLFW/glfw3.h>

#ifndef CONFIG_HPP
#include "config.hpp"
#endif

#include <iostream>

class App {
 public:
  GLFWwindow* window;
  AppConfig* config;

  App();
  void configure(AppConfig* config);
};
