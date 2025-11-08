#include "systems/SpotLightSystem.h"
#include "render/uniforms/SpotLightUBO.h"
#include <iostream>

void SpotLightSystem::Update(Coordinator &coordinator,
                         UniformBufferManager &uboManager) {
  SpotLightUBO uboData{};

  int i = 0;
  for (auto it = mEntities.begin();
       it != mEntities.end() && i < MAX_SPOTS; ++it) {
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(*it);
    auto &lightComponent = coordinator.GetComponent<SpotLightComponent>(*it);

    uboData.data[i].intensity = lightComponent.intensity;
    uboData.data[i].lightColor = lightComponent.lightColor;
    
    uboData.data[i].constant = lightComponent.constant;
    uboData.data[i].linear = lightComponent.linear;
    uboData.data[i].quadratic = lightComponent.quadratic;

    uboData.data[i].direction = lightComponent.direction;

    uboData.data[i].cutOff = lightComponent.cutOff;
    uboData.data[i].outerCutOff = lightComponent.outerCufOff;

    uboData.data[i].position = transformComponent.mPosition;
    i++;
  }
  uboData.size = i;
  uboManager.UpdateUBO("SpotLight", uboData);
}
