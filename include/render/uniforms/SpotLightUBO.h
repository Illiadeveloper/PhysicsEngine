#pragma once

#include "glm/ext/vector_float3.hpp"
struct SpotLightUBO {
  alignas(16) glm::vec3 position;
  float cutOff;

  alignas(16) glm::vec3 direction;
  float outerCutOff;

  float linear;
  float constant;
  float quadratic;

  float _padding;

  alignas(16) glm::vec3 lightColor;
  float intensity;
};
