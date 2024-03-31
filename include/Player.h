#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <Model.h>


void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera);
void moveCameraPlayer(Camera* camera, vec3 position, float deltaTime);
void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps);