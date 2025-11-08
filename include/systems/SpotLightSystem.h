#pragma once
#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "managers/UniformBufferManager.h"
#include "components/SpotLightComponent.h"
#include "components/TransformComponent.h"

class SpotLightSystem : public System {
  public:
    void Update(Coordinator &coordinator, UniformBufferManager &uboManager);
};
