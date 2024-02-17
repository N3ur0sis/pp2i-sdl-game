//************************************************************************************//
// Author : Aymeric R.                                                                //   
// Modifications :                                                                    //
// This is just a basic program to make sure the build system works for everyone      //
//************************************************************************************//


#include <SDL2/SDL.h>
#include <stdbool.h>

//Screen dimensions
#define SCREEN_WIDTH    911
#define SCREEN_HEIGHT   667


int main()
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Create window
    SDL_Window *window = SDL_CreateWindow("Basic C SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        // Clear screen
        SDL_RenderClear(renderer);
        // Update screen
        SDL_RenderPresent(renderer);
    }
    //When quit is true we clean up  some shit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}