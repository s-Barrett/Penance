#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>


int main(int argc, char** argv)
{
  
  if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
 
  SDL_Window* window = SDL_CreateWindow(
        "Penance",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL
    );
    if (!window) return 1;
    
    SDL_GLContext glctx = SDL_GL_CreateContext(window);

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;



}
