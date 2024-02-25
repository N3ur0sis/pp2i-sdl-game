#include "Engine.h"

void initOpenGL() {
    gladLoadGLLoader(SDL_GL_GetProcAddress);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//printf("GL version: %s\n", glGetString(GL_VERSION));
}

void engine_quit() {
	SDL_Quit();
	exit(EXIT_FAILURE);
}
