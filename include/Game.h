//
// Created by Victor Davillé on 17/03/2024.
//

// #ifndef PP2I_GAME_H
// #define PP2I_GAME_H

#pragma once
#include <Engine.h>
#include <Light.h>

typedef struct _Player Player;

typedef struct _Game {
    Time* time;
    SDL_Window* window;
    Shader* shader;
    SDL_Event event;

    bool isRunning;
    int width;
    int height;
    char* title;

    pointLight* point;
    struct _Player* player;
} Game;

Game* game_create(int width, int height, char* title);

void game_start(Game* game);

void game_update(Game* game);

void game_render(Game* game);

void game_destroy(Game* game);

#include <Player.h>


// #endif //PP2I_GAME_H
