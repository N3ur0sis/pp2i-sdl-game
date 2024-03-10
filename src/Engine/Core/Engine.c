#include "Engine.h"

void initOpenGL(float width, float height) {
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glViewport(0, 0, width, height);
	glClearColor(.08f,.08f,.08f,0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void engine_quit() {
	SDL_Quit();
	exit(EXIT_FAILURE);
}
