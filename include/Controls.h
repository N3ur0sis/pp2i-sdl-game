#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <Camera.h>
#include <Time.h>



void processInput(SDL_Event* e, bool* running);
void handleKeyBoardEventDown(SDL_Event e);
void handleKeyBoardEventUp(SDL_Event e);
void handleMouseButtonEvent(SDL_Event e);
bool getKeyState(SDL_KeyCode code);
int getMousePosition(int coord); 
void setMousePosition(int coord, float value);
bool getMouseButtonState(int button);
void handleMouseButtonEvent(SDL_Event e);
void handleMouseWheelEvent(SDL_Event e);


#define NB_KEYS 257
#define SHIFT 255


// vec3 treatModelToMoving
void treatMovingInput(vec3 position, vec3 rotation);