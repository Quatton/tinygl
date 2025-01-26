#include "app.hpp"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

void App::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void App::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.ProcessKeyboard(FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.ProcessKeyboard(LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.ProcessKeyboard(RIGHT, deltaTime);
  }
}

void App::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS
#endif

  window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    throw;
  }

  glEnable(GL_DEPTH_TEST);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, [](GLFWwindow *w, double x, double y) {
    static_cast<App *>(glfwGetWindowUserPointer(w))->mouse_callback(w, x, y);
  });
  glfwSetScrollCallback(window, [](GLFWwindow *w, double x, double y) {
    static_cast<App *>(glfwGetWindowUserPointer(w))->scroll_callback(w, x, y);
  });

  cube = new CubeModel();
}

void App::run() {
  Shader ourShader("shaders/shader.vert", "shaders/shader.frag");

  unsigned int texture0;
  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);

  unsigned char *data =
      stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture" << std::endl;
    throw;
  }

  unsigned int texture1;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture" << std::endl;
    throw;
  }

  stbi_image_free(data);

  ourShader.use();
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
  ourShader.setInt("texture2", 1);
  ourShader.setFloat("ratio", ratio);

  while (!glfwWindowShouldClose(window)) {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    ourShader.setFloat("ratio", ratio);
    ourShader.use();

    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight,
        0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    glm::mat4 view = camera.GetViewMatrix();
    ourShader.setMat4("view", view);

    // Render the cubes
    glBindVertexArray(cube->VAO);
    for (unsigned int i = 0; i < 10; i++) {
      auto model = glm::mat4(1.0f);
      model = glm::translate(model, cubes[i].position);
      model = model * glm::mat4_cast(cubes[i].rotation);
      ourShader.setMat4("model", model);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

App::~App() {
  std::cout << "Destroying App" << std::endl;
  glfwTerminate();
}

void App::spawn(CubeObject cube) { cubes.push_back(cube); }

void App::mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  auto xpos = static_cast<float>(xposIn);
  auto ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom
                                // to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void App::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}