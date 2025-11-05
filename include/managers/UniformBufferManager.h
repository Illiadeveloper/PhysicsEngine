#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include "glm/ext/matrix_float4x4.hpp"
#include "glad/glad.h"

class UniformBufferManager {
public:
  struct UBOInfo {
    GLuint id;
    GLuint binding;
    GLsizeiptr size;
  };

  UniformBufferManager() = default;

  template <typename T> //
  void CreateUBO(const std::string &name, GLuint binding) {
    if (mUBOs.count(name)) {
      std::cerr << "UBO \"" << name << "\" already exists!\n";
      return;
    }

    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    mUBOs[name] = {ubo, binding, sizeof(T)};
    std::cout << "Created UBO \"" << name << "\" at binding=" << binding
              << "\n";
  }

  template <typename T> //
  void UpdateUBO(const std::string &name, const T &data, GLintptr offset = 0) {
    auto it = mUBOs.find(name);
    if (it == mUBOs.end()) {
      std::cerr << "UBO \"" << name << "\" not found!\n";
      return;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, it->second.id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(T), &data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  GLuint GetUBO(const std::string &name) const {
    auto it = mUBOs.find(name);
    return (it != mUBOs.end()) ? it->second.id : 0;
  }

  ~UniformBufferManager() {
    for (auto &[name, ubo] : mUBOs) {
      glDeleteBuffers(1, &ubo.id);
    }
    mUBOs.clear();
    std::cout << "UniformBufferManager: all UBOs deleted\n";
  }

private:
  std::unordered_map<std::string, UBOInfo> mUBOs;
};
