//
// Created by Victor Davillé on 17/03/2024.
//

#ifndef PP2I_GAME_H
#define PP2I_GAME_H

#include "Time.h"
#include "Shader.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Player.h"
#include "Window.h"
#include "Engine.h"
#include "Light.h"
#include "Controls.h"
#include "Player.h"

typedef struct Player Player;

typedef struct Game {
    Time* time;
    SDL_Window* window;
    Shader* shader;
    SDL_Event event;

    bool isRunning;
    int width;
    int height;
    char* title;

    pointLight* point;
    Player* player;
} Game;

Game* game_create(int width, int height, char* title);

void game_start(Game* game);

void game_update(Game* game);

void game_render(Game* game);

void game_destroy(Game* game);

#endif //PP2I_GAME_H
