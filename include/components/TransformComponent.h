#pragma once

#include "glm/vec3.hpp"

struct TransformComponent {
  glm::vec3 mPosition{0.0f};
  glm::vec3 mRotation{0.0f};
  glm::vec3 mScale{1.0f};
};
