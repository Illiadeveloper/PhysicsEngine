#include "App.h"
#include "GLFW/glfw3.h"
#include "components/CameraComponent.h"
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"
#include "components/TransformComponent.h"
#include "ecs/Types.h"
#include "glm/ext/vector_float3.hpp"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"
#include "systems/CameraSystem.h"
#include "systems/RenderSystem.h"
#include <GL/gl.h>
#include <iostream>

App::App(int width, int height, const char *title)
    : mWidth(width), mHeight(height) {
  if (!glfwInit()) {
    throw std::runtime_error("Couldn't init glfw");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!mWindow) {
    throw std::runtime_error("Couldn't create a window");
  }

  glfwMakeContextCurrent(mWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Couldn't load GLAD");
  }
  UpdateViewport(mWidth, mHeight);

  glfwSetWindowUserPointer(mWindow, this);
  glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
}
void App::UpdateViewport(int w, int h) {
  this->mWidth = w;
  this->mHeight = h;
  glViewport(0, 0, w, h);
}

void App::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  App *app = static_cast<App *>(glfwGetWindowUserPointer(window));
  if (app)
    app->UpdateViewport(width, height);
}

void App::ECSInit() {
  mCoordinator.Init();
  mCoordinator.RegisterComponent<MeshComponent>();
  mCoordinator.RegisterComponent<ShaderComponent>();
  mCoordinator.RegisterComponent<TransformComponent>();
  mCoordinator.RegisterComponent<CameraComponent>();

  mCoordinator.RegisterSystem<RenderSystem>();

  Signature RenderSignature;
  RenderSignature.set(mCoordinator.GetComponentType<MeshComponent>());
  RenderSignature.set(mCoordinator.GetComponentType<ShaderComponent>());
  RenderSignature.set(mCoordinator.GetComponentType<TransformComponent>());
  mCoordinator.SetSystemSignature<RenderSystem>(RenderSignature);

  mCoordinator.RegisterSystem<CameraSystem>();

  Signature CameraSignature;
  CameraSignature.set(mCoordinator.GetComponentType<CameraComponent>());
  CameraSignature.set(mCoordinator.GetComponentType<TransformComponent>());
  mCoordinator.SetSystemSignature<CameraSystem>(CameraSignature);
}

App::~App() {
  if (mWindow)
    glfwDestroyWindow(mWindow);
  glfwTerminate();
}

// =============== MAIN LOOP =================
void App::Run() {
  MeshManager meshManager;
  ShaderManager shaderManager;

  auto renderer = mCoordinator.GetSystem<RenderSystem>();
  auto cameraSystem = mCoordinator.GetSystem<CameraSystem>();

  Entity camera = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(camera, TransformComponent{});
  mCoordinator.AddComponent(camera, CameraComponent{});
  mCoordinator.GetComponent<CameraComponent>(camera).mPitch = 0.5f;

  Entity entity = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(entity, MeshComponent{meshManager.LoadMesh(
                                        "resources/objects/cube.obj")});
  mCoordinator.AddComponent(entity, ShaderComponent{shaderManager.LoadShader(
                                        "resources/shaders/default.frag",
                                        "resources/shaders/default.vert")});
  mCoordinator.AddComponent(entity, TransformComponent{});

  while (!glfwWindowShouldClose(mWindow)) {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - mLastFrameTime;
    mLastFrameTime = currentTime;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cameraSystem->Update(mCoordinator, deltaTime);

    renderer->Update(
        mCoordinator, meshManager, shaderManager,
        cameraSystem->GetView(mCoordinator),
        cameraSystem->GetProjection(mCoordinator, (float)mWidth / mHeight));

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}
