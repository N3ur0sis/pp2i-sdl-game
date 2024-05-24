/**
 * @file Window.c
 * @brief Implementation of window management functions for the application.
 * @author Aymeric ROBERT
 */

#include "Window.h"
#include <stdlib.h>

/**
 * @brief Creates a new Window instance.
 * 
 * This function initializes SDL and creates an OpenGL context for the specified window.
 * It also sets some attributes for the window and context.
 * 
 * @param width Initial width of the window.
 * @param height Initial height of the window.
 * @param title Title of the window, displayed on the screen.
 * @return Pointer to the created Window instance or NULL on failure.
 */
Window* WindowCreate(int width, int height, const char* title) {
    /* New window object initialized */
    Window* window = (Window*)calloc(1, sizeof(Window));
    if (!window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to allocate memory for Window.\n");
        return NULL;
    }
    window->m_title = title;
    window->m_width = width;
    window->m_height = height;

    /* Initialize SDL with video and audio subsystem of the library */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n", SDL_GetError());
        free(window);
        return NULL;
    }

    /* Specifies version 4.1 Core profile of OpenGL and some attributes */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    /* Create the actual SDL window */
    window->m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    /* Always check if window has been created properly */
    if (!window->m_window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL window: %s\n", SDL_GetError());
        SDL_Quit();
        free(window);
        return NULL;
    }

    /* Create a context and make it current to the SDL window object */
    window->m_context = SDL_GL_CreateContext(window->m_window);
    if (!window->m_context) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->m_window);
        SDL_Quit();
        free(window);
        return NULL;
    }
    SDL_GL_MakeCurrent(window->m_window, window->m_context);

    /* Disable VSYNC for rendering, put 1 to enable */
    SDL_GL_SetSwapInterval(0);

    return window;
}

/**
 * @brief Deletes a Window instance.
 * 
 * This function deletes the OpenGL context and the specified window.
 * 
 * @param window Pointer to the Window instance to delete.
 */
void WindowDelete(Window* window) {
    if (window) {
        /* Clean up resources allocated */
        SDL_GL_DeleteContext(window->m_context);
        SDL_DestroyWindow(window->m_window);
        free(window);
    }
}
