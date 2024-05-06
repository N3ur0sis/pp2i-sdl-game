#pragma once
#include <SDL2/SDL.h>

typedef struct {
    Uint32 lastUpdate;
    Uint32 currentUpdate;
    float deltaTime;
    unsigned int nbFrames;
} Time;
