#pragma once

#include <glm/vec3.hpp>

struct PointLightComponent {
  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  float intensity = 1.0f;
  
  float linear = 1.0f;
  float constant = 0.14f;
  float quadratic = 0.07f;
};
