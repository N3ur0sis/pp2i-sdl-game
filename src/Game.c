//
// Created by Victor Davillé on 17/03/2024.
//

#include "Game.h"

void game_start(Game* game) {
    //Initialize SDL and Create window
    game->window = window_create(game->width, game->height, game->title);
    //Initialize OpenGL and create ViewPort
    engine_start(game->width, game->height);
    //Load and Compile Shaders into OpenGL
    game->shader = LoadShaders("../assets/shaders/default.vs", "../assets/shaders/default.fs");
    useShaders(game->shader->program);
    game->player = player_create("../assets/models/table.obj", "../assets/images/table.png", camera_create(0.0f, 1.0f, 5.0f, game->width, game->height), (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 0.0f, 0.0f}, (vec3){1.0f, 1.0f, 1.0f}, 5.0f, 5.0f);
    //Creating scene light
    vec3 color = {1.0f, 1.0f, 1.0f};
    light_setAmbientLight(game->shader, color, 0.2f);
    vec3 pointColor = {1.0f, 1.0f, 1.0f};
    vec3 pointPosition = {10.0f, 5.0f, -2.0f};
    game->point = light_createPointLight(game->shader, pointColor, pointPosition, 1.0f, 0.09f);
    game->isRunning = true;
}

void game_update(Game* game) {
    game->time->currentUpdate = SDL_GetTicks();
    game->time->deltaTime = (game->time->currentUpdate - game->time->lastUpdate) / 1000.0f;
    while(SDL_PollEvent(&game->event)){
        processInput(game);
    }
    light_updatePointLight(game->shader, game->point);
    cameraControl(game->player->camera);
    player_update(game->player, game->time, game);
    game->time->lastUpdate = game->time->currentUpdate;
}

void game_render(Game* game) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    player_render(game->player, game);
    SDL_GL_SwapWindow(game->window);
}

void game_destroy(Game* game) {
    free(game->time);
    free(game->player);
    free(game->point);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

Game* game_create(int width, int height, char* title) {
    Game* game = (Game*)malloc(sizeof(Game));
    game->time = (Time*)malloc(sizeof(Time));
    game->width = width;
    game->height = height;
    game->title = title;
    return game;
}
