#pragma once

#include "glm/ext/vector_float3.hpp"

struct MaterialUBO {
  alignas(16) glm::vec3 ambient;
  float _pad1;
  alignas(16) glm::vec3 diffuse;
  float _pad2;
  alignas(16) glm::vec3 specular;
  float shininess; 
};
