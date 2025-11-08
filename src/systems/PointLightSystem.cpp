#include "systems/PointLightSystem.h"
#include "components/PointLightComponent.h"
#include "render/uniforms/PointLightUBO.h"

void PointLightSystem::Update(Coordinator &coordinator,
                              UniformBufferManager &uboManager) {
  PointLightUBO uboData{};

  int i = 0;
  for (auto it = mEntities.begin();
       it != mEntities.end() && i < MAX_POINTS; ++it) {
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(*it);
    auto &lightComponent = coordinator.GetComponent<PointLightComponent>(*it);

    uboData.data[i].intensity = lightComponent.intensity;
    uboData.data[i].lightColor = lightComponent.lightColor;

    uboData.data[i].constant = lightComponent.constant;
    uboData.data[i].linear = lightComponent.linear;
    uboData.data[i].quadratic = lightComponent.quadratic;

    uboData.data[i].position = transformComponent.mPosition;
    i++;
  }
  
  uboData.size = i;
  uboManager.UpdateUBO("PointLight", uboData);
}
