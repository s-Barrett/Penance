#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  std::string vertSource = loadFile(vertexPath);
  std::string fragSource = loadFile(fragmentPath);

  unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertSource);
  unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragSource);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);


  int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "Shader Program Link Error:\n" << infoLog << std::endl;
    }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() const
{
  glUseProgram(ID);

}

std::string Shader::loadFile(const std::string& path) const
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) const
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << " Shader Compile Error:\n" << infoLog << std::endl;
    }

    return shader;

}





