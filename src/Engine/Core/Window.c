#include "Window.h"

Window* WindowInit(int width, int height, const char* title) {

	Window* window = (Window*)malloc(sizeof(Window));

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n", SDL_GetError());
		return NULL;
	}

	//Use OpenGL 4.3 core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);


	//Create a SDL window
	window->m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	

	if (window->m_window == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
	}

	// Create a OpenGL Context
	window->m_context = SDL_GL_CreateContext(window->m_window);
    if (window->m_context == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->m_window);
        SDL_Quit();
        return NULL;
    }

	// Enable VSync with the OpenGL context
    SDL_GL_SetSwapInterval(0);

	return window;
}

void WindowDestroy(Window* window){
	SDL_GL_DeleteContext(window->m_context);
    SDL_DestroyWindow(window->m_window);
}
