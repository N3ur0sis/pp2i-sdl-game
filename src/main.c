//************************************************************************************//
// Author : Aymeric R.                                                                //   
// Modifications :                                                                    //
// This is just a basic program to make sure the build system works for everyone      //
//************************************************************************************//

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL.h>
#include <SDL_opengl.h>
#include <stdbool.h>

//Screen dimensions
#define SCREEN_WIDTH    911
#define SCREEN_HEIGHT   667


int main()
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Create window
    SDL_Window *window = SDL_CreateWindow("OpenGL Renderer",
                         SDL_WINDOWPOS_CENTERED, 
                         SDL_WINDOWPOS_CENTERED, 
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    // Exit flag
    bool quit = false;
    // Render Loop
    while(!quit)
    {
        SDL_Event e;
        // Wait for the next event
        SDL_WaitEvent(&e);
        // User requests quit
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }
        // Initialize renderer color white for the background
        glClearColor(1, 0, 1, 1);
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow( window );
    }
    //When quit is true we clean up  some shit
    SDL_DestroyRenderer(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}