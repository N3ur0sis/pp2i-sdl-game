#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <Model.h>


void treatMovingInput(vec3 position, vec3 rotation, float deltaTime, Camera* camera);
void moveCameraPlayer(Camera* camera, vec3 position, float deltaTime);
// void changeCameraSmoothly(Camera* camera, vec3 old_camera, vec3 new_camera, float transitionTime, float deltaTime);