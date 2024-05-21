#include "Menu.h"

void MenuDraw(Application* game) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 24);
    SDL_Color color = {255, 255, 255, 255};
    while (game->isPaused) {
        while (SDL_PollEvent(game->event)) {
            if (game->event->type == SDL_QUIT) {
                game->running = false;
                game->isPaused = false;
            }
            if (game->event->type == SDL_KEYDOWN) {
                if (game->event->key.keysym.sym == SDLK_ESCAPE) {
                    game->isPaused = false;
                }
            }
        }
    }
    (void) game;
}
