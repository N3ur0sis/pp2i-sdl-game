/**
 * @file Window.h
 * @brief Window management functions and definitions for the application.
 * @author Aymeric ROBERT
 */

#pragma once

#include <SDL2/SDL.h>

/**
 * @brief A Window class that handles the SDL_Window holding the application and the OpenGL context associated with it.
 */
typedef struct _Window {
    SDL_Window* m_window;       /**< The SDL window object. */
    SDL_GLContext m_context;    /**< The OpenGL context current to the window. */
    const char* m_title;        /**< Title of the window. */
    unsigned int m_width;       /**< Width of the window, can be modified. */
    unsigned int m_height;      /**< Height of the window, can be modified. */
} Window;

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
 * @note This window struct is mainly used to get the current width and height of the window.
 */
Window* WindowCreate(int width, int height, const char* title);

/**
 * @brief Deletes a Window instance.
 * 
 * This function deletes the OpenGL context and the specified window.
 * 
 * @param window Pointer to the Window instance to delete.
 * @note The object given in the parameter must have been created with the constructor before calling this function.
 */
void WindowDelete(Window* window);
