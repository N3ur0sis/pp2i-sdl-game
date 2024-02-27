#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <Camera.h>
#include <Time.h>



void processInput(SDL_Event* e, bool* done, Camera* camera, Time* time);
