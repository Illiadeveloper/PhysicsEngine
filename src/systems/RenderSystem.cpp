#include "systems/RenderSystem.h"
#include <iostream>

void RenderSystem::Update(Coordinator &coordinator, MeshManager meshManager,
                          ShaderManager shaderManager) {
  for (auto const &entity : mEntities) {
    auto &meshComponent = coordinator.GetComponent<MeshComponent>(entity);
    auto &shaderComponent = coordinator.GetComponent<ShaderComponent>(entity);

    auto mesh = meshManager.GetMesh(meshComponent.mId);
    shaderManager.BindShader(shaderComponent.mId);
    mesh->Draw();
  }
}
