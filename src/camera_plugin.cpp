#include "camera_plugin.hpp"
#include "pipeline.hpp"
#include "window.hpp"

void scroll_callback(GLFWwindow *w, [[maybe_unused]] double x, double y) {
  static_cast<Pipeline *>(glfwGetWindowUserPointer(w))
      ->get_plugin<CameraPlugin>()
      ->ctx.camera.ProcessMouseScroll(static_cast<float>(y));
}

void mouse_callback([[maybe_unused]] GLFWwindow *window, double xposIn,
                    double yposIn) {
  auto cctx = static_cast<Pipeline *>(glfwGetWindowUserPointer(window))
                  ->get_plugin<CameraPlugin>()
                  ->ctx;

  auto xpos = static_cast<float>(xposIn);
  auto ypos = static_cast<float>(yposIn);

  if (cctx.firstMouse) {
    cctx.lastX = xpos;
    cctx.lastY = ypos;
    cctx.firstMouse = false;
  }

  float xoffset = xpos - cctx.lastX;
  float yoffset = cctx.lastY - ypos; // reversed since y-coordinates go from
  // bottom
  // to top

  cctx.lastX = xpos;
  cctx.lastY = ypos;

  cctx.camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode,
                  int action, [[maybe_unused]] int mods) {
  auto camera = static_cast<Pipeline *>(glfwGetWindowUserPointer(window))
                    ->get_plugin<CameraPlugin>()
                    ->ctx.camera;

  auto deltaTime = static_cast<Pipeline *>(glfwGetWindowUserPointer(window))
                       ->ctx->timer->deltaTime;

  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_W:
      camera.ProcessKeyboard(FORWARD, deltaTime);
      break;
    case GLFW_KEY_S:

      camera.ProcessKeyboard(BACKWARD, deltaTime);
      break;

    case GLFW_KEY_A:

      camera.ProcessKeyboard(LEFT, deltaTime);
      break;
    case GLFW_KEY_D:

      camera.ProcessKeyboard(RIGHT, deltaTime);
      break;
    }
  }
}
