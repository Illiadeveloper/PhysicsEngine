#pragma once

#include "glm/ext/vector_float3.hpp"
struct DirectionalLightUBO {
  alignas(16) glm::vec3 direction;
  float _padding;

  alignas(16) glm::vec3 lightColor;
  float intensity;
};
