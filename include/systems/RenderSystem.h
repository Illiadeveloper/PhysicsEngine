#pragma once
#include "components/TransformComponent.h"
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "glm/mat4x4.hpp"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"

class RenderSystem : public System {
public:
  glm::mat4 GetTransformMatrix(TransformComponent transform);
  void Update(Coordinator &coordinator, MeshManager &meshManager, ShaderManager &shaderManager);
};
