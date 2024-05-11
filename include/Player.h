#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <Model.h>
#include <Animator.h>
#include<unistd.h>
#include <Collider.h>

typedef struct _Player{
    Model* playerModel;
    Animator* playerAnimator;
    float health;
    float speed;
    Collider* collider;
    vec3 velocity;
} Player;

Player* playerCreate(char* modelPath);

 void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);
void playerMovement(Player* player, float deltaTime, Camera* camera, Model* enemy);
void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime);
float lerp_float(float a, float b, float t);
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration);