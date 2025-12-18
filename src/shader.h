#pragma once
#include <string>
#include <SDL2/SDL.h>


class Shader {
public:

  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  void use() const;
  unsigned int getID() const {return ID;}

private:

  unsigned int ID;
  std::string loadFile(const std::string& path) const;
  unsigned int compileShader(unsigned int type, const std::string& source) const;
  
};



