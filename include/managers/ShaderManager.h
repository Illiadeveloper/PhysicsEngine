#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "render/Mesh.h"
#include <cstdint>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <unordered_map>

using ShaderId = GLuint;

class ShaderManager {
public:
  ShaderManager() = default;
  ShaderId LoadShader(const std::string &fart, const std::string &vert);

  void BindShader(ShaderId id);
  void UnbindShader();

  void SetMat4(ShaderId id, const std::string &name, const glm::mat4 &matrix);

  GLint GetUniformLocation(ShaderId id, const std::string& name);

  void InvalidateUniformCache(ShaderId id);

  ~ShaderManager();

private:
  std::string GetFileContext(const std::string &path);
  std::vector<ShaderId> mIds;

  std::unordered_map<ShaderId, std::unordered_map<std::string, GLint>> mUniformLocationCache;
};
