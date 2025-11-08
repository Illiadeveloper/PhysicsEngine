#include "systems/DirectionalLightSystem.h"
#include "components/DirectionalLightComponent.h"
#include "render/uniforms/DirectionalLightUBO.h"

void DirectionalLightSystem::Update(Coordinator &coordinator,
                         UniformBufferManager &uboManager) {
  for (auto const &entity : mEntities) {
    auto &lightComponent = coordinator.GetComponent<DirectionalLightComponent>(entity);

    DirectionalLightUBO data{};
    data.intensity = lightComponent.intensity;
    data.lightColor = lightComponent.lightColor;
    data.direction = lightComponent.direction;

    uboManager.UpdateUBO("DirectionalLight", data);
    break;
  }
}
