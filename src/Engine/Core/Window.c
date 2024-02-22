#include "../../../include/Window.h"

SDL_Window* window_create(int width, int height, const char* title) {

    //Create window handler.
	SDL_Window* window;

    //Init SDL.
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "%s\n", SDL_GetError());
		return NULL;
	}else {
        printf("SDL successfully initialized.");
    }

    //Configure SDL props.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Create window for OpenGL.
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    //Configure window props.
	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetWindowResizable(window, SDL_TRUE);
	//SDL_SetWindowGrab(window, SDL_TRUE);
	//SDL_WarpMouseInWindow(window, width/2, height/2);

	if (window == NULL) {
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

    //Create context in order to load openGL.
	SDL_GLContext context = SDL_GL_CreateContext(window);
	(void) context;
    

	return window;
}