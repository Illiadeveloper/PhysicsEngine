#pragma once
#include "glm/vec3.hpp"

struct CameraComponent {
  bool mActive = true;

  glm::vec3 mTarget{0.0f};
  float mDistance = 7.0f;

  float mYaw = 0.0f;                   
  float mPitch = 0.0f;                
  float mMinPitch = -1.5f;           
  float mMaxPitch = 1.5f;           

  bool mAutoRotate = true;
  float mAutoRotateSpeed = 0.5f;

  float mFov = 45.0f;
  float mNearPlane = 0.1f;
  float mFarPlane = 100.0f;
};
