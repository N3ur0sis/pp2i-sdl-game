#include "../../include/Engine.h"
#include "../../include/Window.h"
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 600

//Application entry point.
int main() {
    printf("test");
    //Creating our Window.
    SDL_Window* window = window_create(WIDTH, HEIGHT, "SDL and OpenGL");
    if (window == NULL) {
		engine_quit();
		return EXIT_FAILURE;
	}


    //Initialize OpenGL on our newly created window.
    initOpenGL();
    SDL_Event event;


    //main loop
    bool done = false;
    while(!done) {

        glViewport(0, 0, WIDTH, HEIGHT);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                done = true;
            }
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,0);
        SDL_GL_SwapWindow(window);
    }
    //Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
}