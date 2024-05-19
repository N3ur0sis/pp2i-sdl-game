#include "Window.h"

Window* WindowCreate(int width, int height, const char* title) {

	/* New window object intialized */
	Window* c_window = (Window*)calloc(1,sizeof(Window));
	c_window->m_title = title;
	c_window->m_width = width;
	c_window->m_height = height;

	/* Initialize SDL with only video subsystem of the library */
	if (SDL_Init(SDL_INIT_VIDEO && SDL_INIT_AUDIO) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n", SDL_GetError());
		return NULL;
	}

	/* Specifies version 4.6 Core profile pf OpenGL and some attributes */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);


	/* Create the actual SDL window */
	c_window->m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	/* Always check if window have been created properly*/
	if (c_window->m_window == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
	}

	/* Create a context a make it current to the SDL window object */
	c_window->m_context = SDL_GL_CreateContext(c_window->m_window);
	SDL_GL_MakeCurrent(c_window->m_window,c_window->m_context);
    if (c_window->m_context == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(c_window->m_window);
        SDL_Quit();
        return NULL;
    }

	/* Disable VSYNC for rendering, put 1 to enable */
    SDL_GL_SetSwapInterval(0);

	return c_window;
}

void WindowDelete(Window* window){

	/* Clean up ressources allocated */
	SDL_GL_DeleteContext(window->m_context);
    SDL_DestroyWindow(window->m_window);
	free(window);
}
