#include "systems/RenderSystem.h"
#include "components/TransformComponent.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <iostream>

glm::mat4 RenderSystem::GetTransformMatrix(TransformComponent transform) {
  glm::mat4 model(1.0f);
  model = glm::translate(model, transform.position);
  model = glm::rotate(model, transform.rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, transform.rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, transform.rotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, transform.scale);
  return model;
}

void RenderSystem::Update(Coordinator &coordinator, MeshManager &meshManager,
                          ShaderManager &shaderManager) {
  for (auto const &entity : mEntities) {
    auto &meshComponent = coordinator.GetComponent<MeshComponent>(entity);
    auto &shaderComponent = coordinator.GetComponent<ShaderComponent>(entity);
    auto &transformComponent =
        coordinator.GetComponent<TransformComponent>(entity);
    
    shaderManager.BindShader(shaderComponent.mId);
    shaderManager.SetMat4(shaderComponent.mId, "uModel",
                          GetTransformMatrix(transformComponent));

    auto mesh = meshManager.GetMesh(meshComponent.mId);
    mesh->Draw();
    shaderManager.UnbindShader();
  }
}
