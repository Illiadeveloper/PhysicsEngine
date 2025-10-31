#include "managers/ShaderManager.h"
#include "glm/detail/qualifier.hpp"
#include "render/Mesh.h"
#include <fstream>
#include <iostream>

ShaderId ShaderManager::LoadShader(const std::string &frag,
                                   const std::string &vert) {
  std::string fragStr = GetFileContext(frag);
  std::string vertStr = GetFileContext(vert);

  const char *fragContext = fragStr.c_str();
  const char *vertContext = vertStr.c_str();

  GLuint fragShader, vertShader;
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragContext, NULL);
  glCompileShader(fragShader);

  vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertContext, NULL);
  glCompileShader(vertShader);

  ShaderId program = glCreateProgram();
  glAttachShader(program, fragShader);
  glAttachShader(program, vertShader);

  glLinkProgram(program);

  glDeleteShader(fragShader);
  glDeleteShader(vertShader);

  mIds.push_back(program);

  return program;
}

void ShaderManager::BindShader(ShaderId id) { glUseProgram(id); }
void ShaderManager::UnbindShader() { glUseProgram(0); }

ShaderManager::~ShaderManager() {
  for (auto id : mIds) {
    if (id != 0) {
      glDeleteProgram(id);
    }
    mUniformLocationCache.erase(id);
  }
  mIds.clear();
  mUniformLocationCache.clear();
}

GLint ShaderManager::GetUniformLocation(ShaderId id, const std::string& name) {
  auto& progCache = mUniformLocationCache[id];
  auto it = progCache.find(name);
  if(it != progCache.end()) return it->second;

  GLint loc = glGetUniformLocation(id, name.c_str());
  progCache.emplace(name, loc);
  return loc;
}

void ShaderManager::InvalidateUniformCache(ShaderId id) {
  mUniformLocationCache.erase(id);
}

void ShaderManager::SetMat4(ShaderId id, const std::string &name,
                            const glm::mat4 &matrix) {
  GLint loc = GetUniformLocation(id, name);
  if(loc == -1) {
    return;
  }
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

std::string ShaderManager::GetFileContext(const std::string &path) {
  std::ifstream file(path);
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}
