#include "systems/SpotLightSystem.h"
#include "render/uniforms/SpotLightUBO.h"

void SpotLightSystem::Update(Coordinator &coordinator,
                         UniformBufferManager &uboManager) {
  for (auto const &entity : mEntities) {
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(entity);
    auto &lightComponent = coordinator.GetComponent<SpotLightComponent>(entity);

    SpotLightUBO data{};
    data.intensity = lightComponent.intensity;
    data.lightColor = lightComponent.lightColor;
    
    data.constant = lightComponent.constant;
    data.linear = lightComponent.linear;
    data.quadratic = lightComponent.quadratic;

    data.direction = lightComponent.direction;

    data.cutOff = lightComponent.cutOff;
    data.outerCutOff = lightComponent.outerCufOff;

    data.position = transformComponent.mPosition;

    uboManager.UpdateUBO("SpotLight", data);
    break;
  }
}
