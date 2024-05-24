#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <Time.h>
#include <GameState.h>



void processInput(SDL_Event* e, bool* running, bool* isPaused, GameState* gameState);
void handleKeyBoardEventDown(SDL_Event e);
void handleKeyBoardEventUp(SDL_Event e);
void handleMouseButtonEvent(SDL_Event e);
bool getKeyState(SDL_KeyCode code);
int getMousePosition(int coord); 
void setMousePosition(int coord, float value);
bool getMouseButtonState(int button);
void handleMouseButtonEvent(SDL_Event e);
void handleMouseWheelEvent(SDL_Event e);
void setKeyState(SDL_KeyCode code, bool state);


#define NB_KEYS 258
#define SHIFT 255
#define TAB 256
#define ESCAPE 257


// vec3 treatModelToMoving
# define    PI	    3.141592