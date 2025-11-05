#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"

struct CameraUBO {
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 projection;
  alignas(16) glm::vec3 cameraPos;
  float _padding; // std140
};
