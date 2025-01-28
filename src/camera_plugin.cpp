#include "camera_plugin.hpp"

void scroll_callback(GLFWwindow *w, [[maybe_unused]] double x, double y) {
  static_cast<Pipeline *>(glfwGetWindowUserPointer(w))
      ->get_plugin<CameraPlugin>()
      ->ctx->camera->ProcessMouseScroll(static_cast<float>(y));
}

void mouse_callback([[maybe_unused]] GLFWwindow *window, double xposIn,
                    double yposIn) {
  auto *cctx = static_cast<Pipeline *>(glfwGetWindowUserPointer(window))
                   ->get_plugin<CameraPlugin>()
                   ->ctx.get();

  auto xpos = static_cast<float>(xposIn);
  auto ypos = static_cast<float>(yposIn);

  if (cctx->firstMouse) {
    cctx->lastX = xpos;
    cctx->lastY = ypos;
    cctx->firstMouse = false;
  }

  float xoffset = xpos - cctx->lastX;
  float yoffset = cctx->lastY - ypos; // reversed since y-coordinates go from
  // bottom
  // to top

  cctx->lastX = xpos;
  cctx->lastY = ypos;

  cctx->camera->ProcessMouseMovement(xoffset, yoffset);
}
