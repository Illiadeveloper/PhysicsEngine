#pragma once
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_int4.hpp"

constexpr int MAX_DIRECTIONALS = 4;

struct DirectionalLightData {
  alignas(16) glm::vec3 direction;
  float _padding;

  alignas(16) glm::vec3 lightColor;
  float intensity;
};

struct DirectionalLightUBO {
  int lightCount; // x = lightCount
  float _pad1, _pad2, _pad3;
  alignas(16) DirectionalLightData directionalLights[MAX_DIRECTIONALS] ;
};
