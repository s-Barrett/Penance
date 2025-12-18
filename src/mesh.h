#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh
{
  public:

    Mesh(const std::vector<float>& vertices);
    void draw() const;

    ~Mesh();

  private:
    unsigned int VAO, VBO;
    size_t vertexCount;
};
