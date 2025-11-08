#include "systems/PointLightSystem.h"
#include "components/PointLightComponent.h"
#include "render/uniforms/PointLightUBO.h"

void PointLightSystem::Update(Coordinator &coordinator,
                         UniformBufferManager &uboManager) {
  for (auto const &entity : mEntities) {
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(entity);
    auto &lightComponent = coordinator.GetComponent<PointLightComponent>(entity);

    PointLightUBO data{};
    data.intensity = lightComponent.intensity;
    data.lightColor = lightComponent.lightColor;

    data.constant = lightComponent.constant;
    data.linear = lightComponent.linear;
    data.quadratic = lightComponent.quadratic;

    data.position = transformComponent.mPosition;

    uboManager.UpdateUBO("PointLight", data);
    break;
  }
}
