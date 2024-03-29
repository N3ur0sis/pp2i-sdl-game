#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <Window.h>
#include <Controls.h>

typedef struct _Application{
    Window* window;
    Time* time;
    SDL_Event* event;
    bool running;
}Application;

Application* ApplicationCreate(int width, int height, const char* title);
void StartFrame(Application* game);
void EndFrame(Application* game);

void EngineInit(void);
void EngineQuit(void);
