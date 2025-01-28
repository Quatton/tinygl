#include "main.hpp"
#include "builder.hpp"
#include "camera_plugin.hpp"

const glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

int main() {

  auto app = PipelineBuilder().add_plugin<CameraPlugin>().build();

  // for (int i = 0; i < 10; i++) {
  // app->spawn(
  //     CubeObject(cubePositions[i],
  //                (glm::quat)glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
  //                                       glm::radians(20.0f * i),
  //                                       glm::vec3(1.0f, 0.3f, 0.5f))));
  // }

  app->run();

  return 0;
}

// void Pipeline::render() {
//   auto *camera = ctx.plugins->get();
//   auto *window = ctx->window.get();
//   glm::mat4 view = camera->GetViewMatrix();
//   glm::mat4 projection = glm::perspective(
//       glm::radians(camera->Zoom), (float)window->width /
//       (float)window->height, 0.1f, 100.0f);

//   for (auto [sID, s] : ctx->shaders->items) {
//     s.use();
//     s.setMat4("projection", projection);
//     s.setMat4("view", view);

//     for (auto r_obj : s.usedBy) {
//       auto obj = r_obj.get();
//       auto model = glm::mat4(1.0f);
//       model = glm::translate(model, obj.position);
//       model = model * glm::mat4_cast(obj.rotation);
//       s.setMat4("model", model);

//       obj.draw();
//     }
//   }
// }

// void load_texture(TextureServer &server) {
//   server.container = TextureLoader()
//                          .from_path("textures/container.jpg")
//                          .set_wrap_s(Wrap::REPEAT)
//                          .set_wrap_t(Wrap::REPEAT)
//                          .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
//                          .set_mag_filter(MagFilter::NEAREST)
//                          .set_flip_vertically(true)
//                          .load()
//                          .release();

//   server.awesomeface = TextureLoader()
//                            .from_path("textures/awesomeface.png")
//                            .set_wrap_s(Wrap::REPEAT)
//                            .set_wrap_t(Wrap::REPEAT)
//                            .set_min_filter(MinFilter::LINEAR_MIPMAP_LINEAR)
//                            .set_mag_filter(MagFilter::NEAREST)
//                            .set_flip_vertically(true)
//                            .set_alpha_channel(true)
//                            .load()
//                            .release();
// }

// void registerCallbacks(App &app) {
//   glfwSetInputMode(app.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//   glfwSetWindowUserPointer(app.window, &app);
//   glfwSetCursorPosCallback(app.window, [](GLFWwindow *w, double x, double y)
//   {
//     static_cast<App *>(glfwGetWindowUserPointer(w))->mouse_callback(w, x, y);
//   });
//   glfwSetScrollCallback(app.window, [](GLFWwindow *w, double x, double y) {
//     static_cast<App *>(glfwGetWindowUserPointer(w))->scroll_callback(w, x,
//     y);
//   });
// }

// void initShapes() {
//   cube = new CubeModel();

//   unsigned int lightVAO;
//   glGenVertexArrays(1, &lightVAO);
//   glBindVertexArray(lightVAO);
//   // we only need to bind to the VBO, the container's VBO's data already
//   // contains the data.
//   glBindBuffer(GL_ARRAY_BUFFER, cube->VBO);
//   // set the vertex attribute
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
//   *)0); glEnableVertexAttribArray(0);
// }

// void App::initShaders() {
//   shader = new Shader("shaders/shader.vert", "shaders/shader.frag");
// }

// void mouse_callback([[maybe_unused]] GLFWwindow *window, double xposIn,
//                     double yposIn) {
//   auto xpos = static_cast<float>(xposIn);
//   auto ypos = static_cast<float>(yposIn);

//   if (firstMouse) {
//     lastX = xpos;
//     lastY = ypos;
//     firstMouse = false;
//   }

//   float xoffset = xpos - lastX;
//   float yoffset = lastY - ypos; // reversed since y-coordinates go from
//   bottom
//                                 // to top

//   lastX = xpos;
//   lastY = ypos;

//   camera.ProcessMouseMovement(xoffset, yoffset);
// }

// void App::scroll_callback([[maybe_unused]] GLFWwindow *window,
//                           [[maybe_unused]] double xoffset, double yoffset) {
//   camera.ProcessMouseScroll(static_cast<float>(yoffset));
// }
