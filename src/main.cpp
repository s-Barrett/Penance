#include <glad/glad.h>
#include <iostream>

#include <SDL.h>
#include <SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include "mesh.h"
#include "shader.h"
#include "ui.h"

std::vector<float> triangleVertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                       0.0f,  0.0f,  0.5f, 0.0f};

int main(int argc, char **argv) {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
    return -1;
  }

  // Set OpenGL version and profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create the window
  SDL_Window *window = SDL_CreateWindow("Penance", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 800, 600,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    return -1;
  }

  // Create the OpenGL context
  SDL_GLContext glctx = SDL_GL_CreateContext(window);
  if (!glctx) {
    std::cerr << "Failed to create GL context: " << SDL_GetError() << std::endl;
    return -1;
  }
  SDL_GL_MakeCurrent(window, glctx);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Shader shader("../assets/shaders/triangle.vert",
                "../assets/shaders/triangle.frag");

  Mesh triangleMesh(triangleVertices);

  UI ui(window);

  bool running = true;
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e)) {

      ui.processEvent(e);

      if (e.type == SDL_QUIT)
      running = false;
    }
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    float time = SDL_GetTicks() / 1000.0f;
    glUniform1f(glGetUniformLocation(shader.getID(), "iTime"), time);
    glUniform2f(glGetUniformLocation(shader.getID(), "iResolution"), 800.0f,
                600.0f);

    triangleMesh.draw();

    ui.beginFrame(); // start ImGui frame
    ui.endFrame();   // render ImGui windows

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(glctx);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
