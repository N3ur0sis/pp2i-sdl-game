#pragma once
#include <SDL2/SDL.h>

typedef struct _Window{
    SDL_Window* m_window;
    SDL_GLContext m_context;
} Window;

Window* WindowInit(int width, int height, const char* title);
void WindowDestroy(Window* window);