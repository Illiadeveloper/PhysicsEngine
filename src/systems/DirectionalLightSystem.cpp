#include "systems/DirectionalLightSystem.h"
#include "components/DirectionalLightComponent.h"
#include "glm/ext/vector_int4.hpp"
#include "render/uniforms/DirectionalLightUBO.h"

void DirectionalLightSystem::Update(Coordinator &coordinator,
                                    UniformBufferManager &uboManager) {
  DirectionalLightUBO uboData{};

  int i = 0;
  for (auto it = mEntities.begin();
       it != mEntities.end() && i < MAX_DIRECTIONALS; ++it) {
    auto &lightComponent =
        coordinator.GetComponent<DirectionalLightComponent>(*it);

    uboData.data[i].intensity = lightComponent.intensity;
    uboData.data[i].lightColor = lightComponent.lightColor;
    uboData.data[i].direction = lightComponent.direction;
    i++;
  }

  uboData.size = i;
  uboManager.UpdateUBO("DirectionalLight", uboData);
}
