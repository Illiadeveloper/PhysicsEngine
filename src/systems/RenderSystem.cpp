#include "systems/RenderSystem.h"
#include "components/LightComponent.h"
#include "components/TransformComponent.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <iostream>
#include <memory>

glm::mat4 RenderSystem::GetTransformMatrix(TransformComponent transform) {
  glm::mat4 model(1.0f);
  model = glm::translate(model, transform.mPosition);
  model = glm::rotate(model, transform.mRotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, transform.mRotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, transform.mRotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, transform.mScale);
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
    // ====== VERTEX SHADER ======
    shaderManager.SetMat4(shaderComponent.mId, "uModel",
                          GetTransformMatrix(transformComponent));

    // ====== FRAG SHADER ==============
    shaderManager.SetVec3(shaderComponent.mId, "uObjectColor",
                          shaderComponent.mObjectColor);

    auto mesh = meshManager.GetMesh(meshComponent.mId);
    mesh->Draw();
    shaderManager.UnbindShader();
  }
}
