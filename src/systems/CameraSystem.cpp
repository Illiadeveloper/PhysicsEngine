#include "systems/CameraSystem.h"
#include "components/CameraComponent.h"
#include "components/TransformComponent.h"
#include "ecs/Coordinator.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include <algorithm>
#include <iostream>

void CameraSystem::Update(Coordinator &coordinator, float deltaTime) {
  for (auto const &entity : mEntities) {
    auto &camera = coordinator.GetComponent<CameraComponent>(entity);
    if (!camera.mActive)
      continue;

    if (camera.mAutoRotate) {
      camera.mYaw += camera.mAutoRotateSpeed * deltaTime;
    }

    glm::vec3 position;
    position.x = camera.mTarget.x + camera.mDistance * cos(camera.mPitch) *
                 sin(camera.mYaw);
    position.y = camera.mTarget.y + camera.mDistance * sin(camera.mPitch);
    position.z = camera.mTarget.z + camera.mDistance * cos(camera.mPitch) *
                 cos(camera.mYaw);

    auto &transform = coordinator.GetComponent<TransformComponent>(entity);
    transform.mPosition = position;
    transform.mRotation = glm::vec3(camera.mPitch, camera.mYaw, 0.0f);
  }
}

glm::mat4 CameraSystem::GetView(Coordinator &coordinator) {
  for (auto const &entity : mEntities) {
    auto &camera = coordinator.GetComponent<CameraComponent>(entity);
    if (!camera.mActive)
      continue;

    auto &transform = coordinator.GetComponent<TransformComponent>(entity);

    return glm::lookAt(transform.mPosition, camera.mTarget,
                       glm::vec3(0.0f, 1.0f, 0.0f));
  }
  return glm::mat4(1.0f);
}

glm::mat4 CameraSystem::GetProjection(Coordinator &coordinator,
                                      float aspectRatio) {
  for (auto const &entity : mEntities) {
    auto &camera = coordinator.GetComponent<CameraComponent>(entity);
    if (!camera.mActive)
      continue;

    auto &transform = coordinator.GetComponent<TransformComponent>(entity);

    return glm::perspective(glm::radians(camera.mFov), aspectRatio,
                            camera.mNearPlane, camera.mFarPlane);
  }
  return glm::mat4(1.0f);
}
