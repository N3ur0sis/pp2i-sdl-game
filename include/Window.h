#pragma once
#include <SDL2/SDL.h>

/**
 * A Window class that handles the window holding the application and the 
 * OpenGL context Associated to it. 
*/
typedef struct _Window{
    SDL_Window* m_window;       /* The SDL window object */
    SDL_GLContext m_context;    /* The OpenGL context current to the window*/
    const char* m_title;          /* Title of the window */
    unsigned int m_width;       /* Width of the window, can be mopdified */
    unsigned int m_height;      /* Height of the window, can be modified */
} Window;

/**
 * A Window connstructor, calling this function will initialize SDL ang create
 * a context for this specific window, it will also set some attributes for the window/context
 * 
 * @param width Initial width of the window
 * @param height Initial height of the window
 * @param title Name of the window, will be printed on screen
 * @return Handle to an Engine Window
 * @note This window struct will essentially be used to get the current width and height of the window.   
*/
Window* WindowCreate(int width, int height, const char* title);
/**
 * Window destructor, simply delete the context and window given in arguments.
 * @param window a window object
 * @note The object given in parameters must have been created with construcor before calling this function 
*/
void WindowDelete(Window* window);