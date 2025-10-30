#include "App.h"
#include "GLFW/glfw3.h"
#include "components/MeshComponent.h"
#include "components/ShaderComponent.h"
#include "ecs/Types.h"
#include "managers/MeshManager.h"
#include "managers/ShaderManager.h"
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

  mCoordinator.RegisterSystem<RenderSystem>();

  Signature signature;
  signature.set(mCoordinator.GetComponentType<MeshComponent>());
  signature.set(mCoordinator.GetComponentType<ShaderComponent>());
  mCoordinator.SetSystemSignature<RenderSystem>(signature);
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

  Entity entity = mCoordinator.CreateEntity();
  mCoordinator.AddComponent(entity, MeshComponent{meshManager.LoadMesh(
                                        "resources/objects/cube.obj")});
  mCoordinator.AddComponent(entity, ShaderComponent{shaderManager.LoadShader(
                                        "resources/shaders/default.frag",
                                        "resources/shaders/default.vert")});

  while (!glfwWindowShouldClose(mWindow)) {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - mLastFrameTime;
    mLastFrameTime = currentTime;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->Update(mCoordinator, meshManager, shaderManager);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}
