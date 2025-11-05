#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "App.h"
#include "render/Mesh.h"
#include "ecs/Coordinator.h"
#include "glm/detail/qualifier.hpp"

// ===== PLANS =====
// 1. ECS change const char* to type_index
// 2. Make commits about it all
// 3. Commit it like minimum version
// 4. Add READ ME file
// 5. Look at the code, and maybe make refactoring

int main (int argc, char *argv[]) {
  App app = App(800, 800, "ECS");
  app.Init();
  app.Run();
  return 0;
}
