#pragma once

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <glm/glm.hpp>
#include <vector>

#include "camera.hpp"
#include "const.hpp"
#include "model/model.hpp"
#include "object/object.hpp"

#include "shader.hpp"
#include "texture.hpp"

#include <iostream>

class App {
  friend class AppBuilder;

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

  Camera camera;

  void insert_texture(Texture texture);
  void spawn(CubeObject cube);

  void run();

private:
  void initGLFW();
  void initGLAD();
  void registerCallbacks();
  void initShapes();
  void initShaders();

  Shader *shader;

  /// Will be loop through internally
  CubeModel *cube;
  std::vector<CubeObject> cubes;

  std::vector<Texture> textures;

  /// Will be accessed by builder
  void init();

  // Callbacks
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
  void processInput(GLFWwindow *window);
};
