#include "App.h"
#include "GLFW/glfw3.h"
#include "components/CameraComponent.h"
#include "components/LightComponent.h"
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"
#include "components/TransformComponent.h"
#include "ecs/Types.h"
#include "glm/ext/vector_float3.hpp"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"
#include "render/uniforms/CameraUBO.h"
#include "render/uniforms/LightUBO.h"
#include "systems/CameraSystem.h"
#include "systems/LightSystem.h"
#include "systems/RenderSystem.h"
#include <GL/gl.h>
#include <iostream>

App::App(int width, int height, const char *title)
    : mWidth(width), mHeight(height), mLastFrameTime(0) {
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

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void App::Init() {
  mUniformManager.CreateUBO<CameraUBO>("Camera", 0);
  mUniformManager.CreateUBO<LightUBO>("Light", 1);

  mCoordinator.Init();
  mCoordinator.RegisterComponent<MeshComponent>();
  mCoordinator.RegisterComponent<ShaderComponent>();
  mCoordinator.RegisterComponent<TransformComponent>();
  mCoordinator.RegisterComponent<CameraComponent>();
  mCoordinator.RegisterComponent<LightComponent>();

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

  mCoordinator.RegisterSystem<LightSystem>();
  Signature LightSignature;
  LightSignature.set(mCoordinator.GetComponentType<LightComponent>());
  LightSignature.set(mCoordinator.GetComponentType<TransformComponent>());
  mCoordinator.SetSystemSignature<LightSystem>(LightSignature);
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
  auto lightSystem = mCoordinator.GetSystem<LightSystem>();

  Entity camera = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(camera, TransformComponent{});
  mCoordinator.AddComponent(camera, CameraComponent{});

  mCoordinator.GetComponent<CameraComponent>(camera).mPitch = 0.5f;
  mCoordinator.GetComponent<CameraComponent>(camera).mDistance = 10.0f;
  mCoordinator.GetComponent<CameraComponent>(camera).mFov = 60.0f;

  Entity light = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(light,
                            LightComponent{glm::vec3(1.0f, 1.0f, 1.0f), 1.0f});
  mCoordinator.AddComponent(light,
                            TransformComponent{glm::vec3(0.0f, 2.0f, 1.0f)});
  //
  Entity surface = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(surface, MeshComponent{meshManager.LoadMesh(
                                         "resources/objects/surface.obj")});
  mCoordinator.AddComponent(surface, ShaderComponent{shaderManager.LoadShader(
                                         "resources/shaders/cube1.frag",
                                         "resources/shaders/default.vert"),
      glm::vec3(0.3f, 0.3f, 0.3f)});
  mCoordinator.AddComponent(
      surface, TransformComponent{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f),
                                  glm::vec3(7.0f)});
  
  Entity cube1 = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(
      cube1, MeshComponent{meshManager.LoadMesh("resources/objects/cube.obj")});
  mCoordinator.AddComponent(
      cube1, ShaderComponent{
                 shaderManager.LoadShader("resources/shaders/cube1.frag",
                                          "resources/shaders/default.vert"),
                 glm::vec3(0.5f, 0.5f, 1.0f)});
  mCoordinator.AddComponent(cube1,
                            TransformComponent{glm::vec3(2.0f, 0.0f, 0.0f)});

  Entity cube2 = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(
      cube2, MeshComponent{meshManager.LoadMesh("resources/objects/cube.obj")});
  mCoordinator.AddComponent(
      cube2, ShaderComponent{
                 shaderManager.LoadShader("resources/shaders/cube1.frag",
                                          "resources/shaders/default.vert"),
                 glm::vec3(1.0f, 0.5f, 0.5f)});
  mCoordinator.AddComponent(cube2,
                            TransformComponent{glm::vec3(-2.0f, 0.0f, 0.0f)});

  while (!glfwWindowShouldClose(mWindow)) {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - mLastFrameTime;
    mLastFrameTime = currentTime;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightSystem->Update(mCoordinator, mUniformManager);
    cameraSystem->Update(mCoordinator, deltaTime);
    cameraSystem->UploadToUBO(mCoordinator, mUniformManager,
                              (float)mWidth / mHeight);
    renderer->Update(mCoordinator, meshManager, shaderManager);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}
