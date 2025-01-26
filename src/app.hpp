#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>

#include "camera.hpp"
#include "const.hpp"

class App {
public:
  App() : camera(Camera(glm::vec3(0.0f, 0.0f, 3.0f))) {}
  ~App();

  GLFWwindow *window;

  int majorVersion = 3;
  int minorVersion = 3;

  int windowWidth = SCR_WIDTH;
  int windowHeight = SCR_HEIGHT;

  const char *windowName;

  float deltaTime = 0.0f; // Time between current frame and last frame
  float lastFrame = 0.0f;

  float lastX = SCR_WIDTH / 2.0f;
  float lastY = SCR_HEIGHT / 2.0f;
  bool firstMouse = true;

  float ratio = 0.1f;

  unsigned int VBO, VAO, EBO;

  Camera camera;

  // Callbacks
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
  void processInput(GLFWwindow *window);

  void init();
  void run();
};
