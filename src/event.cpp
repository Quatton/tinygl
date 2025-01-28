// #include "pipeline.hpp"

// void Pipeline::processInput(GLFWwindow *window) {
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//     glfwSetWindowShouldClose(window, true);
//   }

//   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//     camera.ProcessKeyboard(FORWARD, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//     camera.ProcessKeyboard(BACKWARD, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//     camera.ProcessKeyboard(LEFT, deltaTime);
//   }
//   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//     camera.ProcessKeyboard(RIGHT, deltaTime);
//   }
// }

// void setCursorPosCallback(void (*callback)(Context *, GLFWwindow *w, double
// x,
//                                            double y)) const {
//   auto *gw = ctx->window.get().instance;
//   glfwSetCursorPosCallback(gw, [](GLFWwindow *w, double x, double y) {

//   });
// }

// void setScrollCallback(void (*callback)(Context *, GLFWwindow *w, double x,
//                                         double y)) const {
//   auto *gw = ctx->window.get().instance;
//   glfwSetCursorPosCallback(gw, callback);
// }

// std::reference_wrapper<void(Context *, GLFWwindow *p)> processInput;

// void event_loop() const {
//   auto *gw = ctx->window.get().instance;
//   while (!glfwWindowShouldClose(gw)) {
//     ctx->timer.get().tick();
//     processInput(ctx.get(), gw);

//     ctx->window.get().clear();

//     renderer->draw();

//     glfwSwapBuffers(gw);
//     glfwPollEvents();
//   }
// }

// //
// void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int
// width,
//                                int height) {
//   glViewport(0, 0, width, height);
// }
