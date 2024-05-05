#include "Menu.h"

void renderPauseMenu(Application* game) {
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    TTF_Font* font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 24);
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(2);
    }

    (void) game;

    SDL_Color color = {255, 255, 255, 255}; 
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Paused", color);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
}
