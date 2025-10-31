#pragma once
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"
#include "components/TransformComponent.h"
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "glm/mat4x4.hpp"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"

class RenderSystem : public System {
public:
  glm::mat4 GetTransformMatrix(TransformComponent transform);
  void Update(Coordinator &coordinator, MeshManager &meshManager,
              ShaderManager &shaderManager, const glm::mat4 &view,
              const glm::mat4 &projection);
};
