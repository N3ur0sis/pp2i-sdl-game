#include "Window.h"

SDL_Window* window_create(int width, int height, const char* title) {

	SDL_Window* window;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return NULL;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetSwapInterval(0); 

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowResizable(window, SDL_TRUE);
	//SDL_SetWindowGrab(window, SDL_TRUE);
	//SDL_WarpMouseInWindow(window, 0, 0);

	if (window == NULL) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
    (void) context;

	return window;
}
