#pragma once
#include <SDL2/SDL.h>

typedef struct {
    uint32_t lastUpdate;
    uint32_t currentUpdate;
    float deltaTime;
} Time;
