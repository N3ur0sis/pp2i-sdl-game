#include "Engine.h"


void initOpenGL() {

	gladLoadGLLoader(SDL_GL_GetProcAddress);
	//glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
}

void engine_quit() {
	SDL_Quit();
	exit(EXIT_FAILURE);
}   