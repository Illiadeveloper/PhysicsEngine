#include "managers/ShaderManager.h"
#include "render/Mesh.h"
#include <fstream>
#include <iostream>

ShaderId ShaderManager::LoadShader(const std::string &frag, const std::string &vert) {
  std::string fragStr = GetFileContext(frag);
  std::string vertStr = GetFileContext(vert);

  const char* fragContext = fragStr.c_str();
  const char* vertContext = vertStr.c_str();

  GLuint fragShader, vertShader;
  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragContext, NULL);
  glCompileShader(fragShader);

  vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertContext, NULL);
  glCompileShader(vertShader);

  ShaderId Id = glCreateProgram();
  glAttachShader(Id, fragShader);
  glAttachShader(Id, vertShader);

  glLinkProgram(Id);
  
  glDeleteShader(fragShader);
  glDeleteShader(vertShader);

  mIds.push_back(Id);

  return Id;
}

void ShaderManager::BindShader(ShaderId id) {glUseProgram(id);}
void ShaderManager::UnbindShader() {glUseProgram(0);}

ShaderManager::~ShaderManager() {
  for(int i = 0; i < mIds.size(); ++i) {
    glDeleteProgram(mIds[i]);
  }
}

std::string ShaderManager::GetFileContext(const std::string &path) {
  std::ifstream file(path);
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}
