#pragma once
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "glm/ext/matrix_float4x4.hpp"
class CameraSystem : public System {
public:
  void Update(Coordinator& coordinator, float deltaTime);
  glm::mat4 GetView(Coordinator& coordinator);
  glm::mat4 GetProjection(Coordinator& coordinator, float aspectRatio);
};
