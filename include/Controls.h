#pragma once
#include <stdbool.h>
#include <Time.h>
#include "Game.h"


void processInput(Game* game);
void handleKeyBoardEvent(SDL_Event e);
void handleMouseButtonEvent(SDL_Event e);
bool getKeyState(SDL_KeyCode code);
int getMousePosition(int coord); 
void setMousePosition(int coord, float value);
bool getMouseButtonState(int button);
void handleMouseButtonEvent(SDL_Event e);
void handleMouseWheelEvent(SDL_Event e);
