#pragma once

#include "glm/ext/vector_float3.hpp"

constexpr int MAX_SPOTS = 16;

struct SpotLightData {
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

struct SpotLightUBO {
  int size; 
  float _pad1, _pad2, _pad3;
  alignas(16) SpotLightData data[MAX_SPOTS];
};
