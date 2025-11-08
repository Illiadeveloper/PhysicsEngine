#include "systems/DirectionalLightSystem.h"
#include "components/DirectionalLightComponent.h"
#include "glm/ext/vector_int4.hpp"
#include "render/uniforms/DirectionalLightUBO.h"

void DirectionalLightSystem::Update(Coordinator &coordinator,
                                    UniformBufferManager &uboManager) {
  DirectionalLightUBO uboData{};

  int count_it = 0;
  for (auto it = mEntities.begin();
       it != mEntities.end() && count_it < MAX_DIRECTIONALS; ++it) {
    auto &lightComponent =
        coordinator.GetComponent<DirectionalLightComponent>(*it);

    uboData.directionalLights[count_it].intensity = lightComponent.intensity;
    uboData.directionalLights[count_it].lightColor = lightComponent.lightColor;
    uboData.directionalLights[count_it].direction = lightComponent.direction;
    count_it++;
  }

  uboData.lightCount = count_it;
  uboManager.UpdateUBO("DirectionalLight", uboData);
}
