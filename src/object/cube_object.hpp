#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class CubeObject {
public:
  CubeObject(glm::vec3 position = glm::vec3(0.0f),
             glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
      : position(position), rotation(rotation) {}

  glm::vec3 position;
  glm::quat rotation;

  ~CubeObject() = default;
};