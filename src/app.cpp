#include "app.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

App::App() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->config->majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->config->minorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS
#endif

  this->window =
      glfwCreateWindow(this->config->windowWidth, this->config->windowHeight,
                       this->config->windowName, NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw;
  }
  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}