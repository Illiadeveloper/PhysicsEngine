#pragma once

#include "ecs/Coordinator.h"
#include "ecs/SystemManager.h"
#include "managers/UniformBufferManager.h"
class MaterialSystem : public System {
public:
  void Update(Coordinator &coordinator, UniformBufferManager &uboManager);
};
