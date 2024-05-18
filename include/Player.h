#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include<unistd.h>
#include <Entity.h>


void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);
void playerMovement(Entity* player, float deltaTime, Camera* camera, Model* enemy);
void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime);
float lerp_float(float a, float b, float t);
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration);
bool playerInteract();
