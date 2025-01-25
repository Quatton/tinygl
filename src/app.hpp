
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


class App {
 public:
  GLFWwindow* window;

  int majorVersion;
  int minorVersion;

  int windowWidth;
  int windowHeight;
  
  const char* windowName;

  unsigned int VBO, VAO, EBO;

  void (*inputCallback)(GLFWwindow*);
  void (*eventLoop)();

  App();
  ~App();

  void run();
};

class AppConfig {
 public:
  int majorVersion;
  int minorVersion;

  int windowWidth;
  int windowHeight;
  
  const char* windowName;

  AppConfig();

  void setOpenGLVersion(int majorVersion, int minorVersion);
  void setWindowSize(int width, int height);
  void setWindowName(const char* name);

  [[nodiscard]] App build() const;
};
