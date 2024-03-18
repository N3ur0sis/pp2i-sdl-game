//
// Created by Victor Davillé on 14/03/2024.
//

#ifndef PP2I_PLAYER_H
#define PP2I_PLAYER_H

#include "Mesh.h"
#include "Textures.h"
#include "ReadShader.h"
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include "Time.h"
#include "objLoader.h"
#include <cglm/cglm.h>
#include "Game.h"

typedef struct Game Game;

typedef struct Player {
    Mesh* model;
    Camera* camera;
    vec3 position;
    vec3 rotation;
    vec3 scale;
    float speed;
    float rotationSpeed;
} Player;

Player* player_create(char* objPath, char* texturePath, Camera* camera, vec3 position, vec3 rotation, vec3 scale, float speed, float rotationSpeed);

void player_update(Player* player, Time* time, Game* game);

void player_render(Player* player, Game* game);

#endif //PP2I_PLAYER_H
