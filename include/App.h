#pragma once

#include "glad/glad.h"
//
#include "GLFW/glfw3.h"
#include "ecs/Coordinator.h"
#include <stdexcept>

class App {
public:
  App(int width, int height, const char *title);
  void ECSInit();
  ~App();
  void Run();
  
  void UpdateViewport(int w, int h);
private:
  int mWidth;
  int mHeight;

  float mLastFrameTime;

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int heiht);

  GLFWwindow *mWindow;
  Coordinator mCoordinator;
};
