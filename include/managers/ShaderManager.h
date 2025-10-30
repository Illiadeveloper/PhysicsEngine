#pragma once

#include "render/Mesh.h"
#include <cstdint>
#include <string>

using ShaderId = GLuint;

class ShaderManager {
public:
  ShaderManager() = default;
  ShaderId LoadShader(const std::string &fart, const std::string &vert);

  void BindShader(ShaderId id);
  void UnbindShader();

  ~ShaderManager();
private:
  std::string GetFileContext(const std::string& path);
  std::vector<ShaderId> mIds;
};
