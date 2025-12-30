#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  void use() const;
  unsigned int getID() const { return ID; }

  // generic uniform setter for mat4
  void uniform(const std::string &name, const glm::mat4 &value) const;

private:
  unsigned int ID;
  std::string loadFile(const std::string &path) const;
  unsigned int compileShader(unsigned int type,
                             const std::string &source) const;
};
