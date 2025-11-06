#include "systems/MaterialSystem.h"
#include "components/MaterialComponent.h"
#include "render/uniforms/MaterialUBO.h"
void MaterialSystem::Update(Coordinator &coordinator,
                            UniformBufferManager &uboManager) {
  for(auto const& entity : mEntities) {
    auto& material = coordinator.GetComponent<MaterialComponent>(entity);

    MaterialUBO data{};
    data.ambient = material.ambient;
    data.diffuse = material.diffuse;
    data.specular = material.specular;
    data.shininess = material.shininess;
    std::cout << data.shininess << std::endl;
    uboManager.UpdateUBO("Material", data);
    break;
  }
}
