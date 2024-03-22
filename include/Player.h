//
// Created by Victor Davillé on 14/03/2024.
//

// #ifndef PP2I_PLAYER_H
// #define PP2I_PLAYER_H

#pragma once
#include <Mesh.h>
#include <Textures.h>
#include <ReadShader.h>
#include <Light.h>
#include <objLoader.h>
#include <Game.h>
#include <Camera.h>

// typedef struct _Game Game;

// typedef struct _Camera Camera;


typedef struct _Player {
    struct _Mesh* model;
    struct _Camera* camera;
    vec3 position;
    vec3 rotation;
    vec3 scale;
    float speed;
    float rotationSpeed;
} Player;

Player* player_create(char* objPath, char* texturePath, Camera* camera, vec3 position, vec3 rotation, vec3 scale, float speed, float rotationSpeed);

void player_update(Player* player, Time* time, Game* game);

void player_render(Player* player, Game* game);

// #endif //PP2I_PLAYER_H
