#pragma once
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "managers/UniformBufferManager.h"
#include "components/LightComponent.h"
#include "components/TransformComponent.h"
#include "render/uniforms/LightUBO.h"

class LightSystem : public System {
  public:
    void Update(Coordinator &coordinator, UniformBufferManager &uboManager);
};
