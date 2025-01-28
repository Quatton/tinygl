#pragma once

#include <any>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Object {
public:
  unsigned int ID;

  Object(glm::vec3 position = glm::vec3(0.0f),
         glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
      : position(position), rotation(rotation) {}

  glm::vec3 position;
  glm::quat rotation;
  std::optional<std::reference_wrapper<class Model>> model;

  ~Object() = default;
};
