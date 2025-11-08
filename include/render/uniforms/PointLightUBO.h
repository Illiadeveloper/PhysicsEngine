#pragma once

#include "glm/ext/vector_float3.hpp"
struct PointLightUBO {
  alignas(16) glm::vec3 position;
  float linear;

  alignas(16) glm::vec3 lightColor;
  float intensity;

  float constant;
  float quadratic;

  float _padding1;
  float _padding2;
};
