#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <Model.h>
#include<unistd.h>

typedef struct _Player{
    float Health;
    float Speed;
    vec3 position;
    vec4 rotation;
} Player;

void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera, vec3 playerbb[2], vec3 playerbbo[2], vec3 treebb[2], Model* map);
void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime);
void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration);