#pragma once
#include "glm/ext/vector_float3.hpp"

constexpr int MAX_DIRECTIONALS = 4;

struct DirectionalLightData {
  alignas(16) glm::vec3 direction;
  float _padding;

  alignas(16) glm::vec3 lightColor;
  float intensity;
};

struct DirectionalLightUBO {
  int size; 
  float _pad1, _pad2, _pad3;
  alignas(16) DirectionalLightData data[MAX_DIRECTIONALS] ;
};
