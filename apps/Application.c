#include <Game.h>


//Entry Point of the Game
int main(void){
    Game* game = game_create(1280, 720, "Game");

    game_start(game);

    while(game->isRunning) {
        game_update(game);
        game_render(game);
    }
    game_destroy(game);
}
