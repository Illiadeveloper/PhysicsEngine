#pragma once

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

struct SpotLightComponent {
  glm::vec3 lightColor{1.0f, 1.0f, 1.0f};
  float intensity = 1.0f;
  
  glm::vec3 direction{0.0f, -1.0f, 0.0f};

  float cutOff = glm::cos(glm::radians(12.5f));
  float outerCufOff = 0.953;
  
  float linear = 1.0f;
  float constant = 0.14f;
  float quadratic = 0.07f;
};
