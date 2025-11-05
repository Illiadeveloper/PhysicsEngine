#pragma once
#include <glm/vec3.hpp>

struct LightComponent {
  glm::vec3 color{1.0f};
  float intensity = 1.0f;
};
