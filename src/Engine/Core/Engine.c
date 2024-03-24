#include "Engine.h"

void GL_Init(void){

	//Init Glad and configure basic rendering properties.
    gladLoadGLLoader(SDL_GL_GetProcAddress);

	// Set up initial GL attributes
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Set the cleared back buffer to dark gray
    glCullFace(GL_BACK);                  // Set back-face culling
    glEnable(GL_CULL_FACE);               // Enable use of back/front face culling
    glEnable(GL_DEPTH_TEST);              // Enable use of depth testing
    glDisable(GL_STENCIL_TEST);           // Disable stencil test for speed
    printf("OpenGL version supported by this platform (%s): \n",
        glGetString(GL_VERSION));
}

void GL_Quit(void) {
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
