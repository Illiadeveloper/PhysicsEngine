#include "systems/LightSystem.h"

void LightSystem::Update(Coordinator &coordinator,
                         UniformBufferManager &uboManager) {
  for (auto const &entity : mEntities) {
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(entity);
    auto &lightComponent = coordinator.GetComponent<LightComponent>(entity);

    LightUBO data{};
    data.intensity = lightComponent.intensity;
    data.lightColor = lightComponent.color;
    data.lightPos = transformComponent.mPosition;

    uboManager.UpdateUBO("Light", data);
    break;
  }
}
