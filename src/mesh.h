#pragma once
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  Mesh(const std::vector<glm::vec3> &vertices);
  void draw() const;

  ~Mesh();

private:
  unsigned int VAO, VBO;
  size_t vertexCount;
};
