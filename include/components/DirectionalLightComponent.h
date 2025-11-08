#pragma once

#include <glm/vec3.hpp>

struct DirectionalLightComponent {
  glm::vec3 direction{0.0f, -1.0f, 0.0f};
  glm::vec3 lightColor{1.0f, 1.0f, 1.0f};
  float intensity = 1.0f;
};
