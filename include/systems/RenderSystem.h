#pragma once
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"

class RenderSystem : public System {
public:
  void Update(Coordinator &coordinator, MeshManager meshManager, ShaderManager shaderManager);
};
