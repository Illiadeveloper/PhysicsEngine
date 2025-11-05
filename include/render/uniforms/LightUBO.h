#pragma once

#include "glm/ext/vector_float3.hpp"
struct LightUBO {
  alignas(16) glm::vec3 lightPos;
  float intensity;
  alignas(16) glm::vec3 lightColor;
  float _padding2;
};
