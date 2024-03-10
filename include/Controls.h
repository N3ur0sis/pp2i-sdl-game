#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <Camera.h>
#include <Time.h>



void processInput(SDL_Event* e, bool* done);
void handleKeyBoardEvent(SDL_Event e);
void handleMouseButtonEvent(SDL_Event e);
bool getKeyState(SDL_KeyCode code);
int getMousePosition(int coord); 
void setMousePosition(int coord, float value);
bool getMouseButtonState(int button);
void handleMouseButtonEvent(SDL_Event e);
void handleMouseWheelEvent(SDL_Event e);