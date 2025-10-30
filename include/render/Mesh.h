#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoord;
};

class Mesh {
public:
  Mesh(const std::vector<Vertex> &vertices,
       const std::vector<unsigned int> &indices);

  void Draw() const;
  inline std::vector<Vertex> getVerices() const { return mVertices; }
  ~Mesh();

private:
  std::vector<Vertex> mVertices;
  std::vector<unsigned int> mIndices;
  GLuint mVAO, mVBO, mEBO;

  void SetupMesh();
};
