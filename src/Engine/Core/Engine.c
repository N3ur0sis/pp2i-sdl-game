#include <Engine.h>

void engine_start(float width, float height){

	//Init Glad and configure basic rendering properties.
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glViewport(0, 0, width, height);
	glClearColor(.08f,.08f,.08f,0);
	//Enable 3D
	glEnable(GL_DEPTH_TEST);
	//Enable face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	//Change to GL_LINE to render in wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void engine_quit(void) {
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
