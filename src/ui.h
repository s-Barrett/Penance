#pragma once

#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

class UI {
public:
  UI(SDL_Window *window) : window(window), showTestWindow(true) {
    // ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    // Initialize backends
    ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
    ImGui_ImplOpenGL3_Init("#version 330");
  }

  ~UI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
  }

  void processEvent(const SDL_Event &event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
  }

  void beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
  }

  void endFrame() {
    // Simple test window
    if (showTestWindow) {
        ImGui::GetIO().IniFilename = nullptr;                  // ignore saved sizes
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Always);
        ImGui::Begin("Test Window");
        ImGui::Text("Hello, ImGui is working!");
        ImGui::Checkbox("Show this window", &showTestWindow);
        ImGui::End();
    } 

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

private:
  SDL_Window *window;
  bool showTestWindow;
};
