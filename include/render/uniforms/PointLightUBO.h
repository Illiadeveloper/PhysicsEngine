#pragma once

#include "glm/ext/vector_float3.hpp"

constexpr int MAX_POINTS = 16;

struct PointLightData {
  alignas(16) glm::vec3 position;
  float linear;

  alignas(16) glm::vec3 lightColor;
  float intensity;

  float constant;
  float quadratic;

  float _padding1;
  float _padding2;
};

struct PointLightUBO {
  int size;
  float _pad1, _pad2, _pad3;
  alignas(16) PointLightData data[MAX_POINTS];
};
