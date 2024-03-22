#include <Controls.h>


//State of Mouse and keyboard input
char keyState[255] = { 0 };
float mousePos[6] = {0}; // 0->posX 1->posY 2->lastX 3->lastY 4->wheely ->5 lastWheelY
char mouseState[5] = { 0 }; // mouse button state


void processInput(Game* game){
	switch (game->event.type) {
		case SDL_QUIT:
			game->isRunning = false;
			break;
		case SDL_KEYDOWN:
			handleKeyBoardEvent(game->event);
			break;
		case SDL_KEYUP:
			handleKeyBoardEvent(game->event);
			break;
		case SDL_MOUSEMOTION:
			mousePos[0] = game->event.motion.x;
			mousePos[1] = game->event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			handleMouseButtonEvent(game->event);
            break;
		case SDL_MOUSEBUTTONUP:
			handleMouseButtonEvent(game->event);
			break;
		case SDL_MOUSEWHEEL:
			handleMouseWheelEvent(game->event);
	}
}

void handleKeyBoardEvent(SDL_Event e){
	keyState[e.key.keysym.sym] = e.key.state;
}

void handleMouseButtonEvent(SDL_Event e){
	mouseState[e.button.button] = e.button.state;
}

void handleMouseWheelEvent(SDL_Event e){
	mousePos[4] += e.wheel.y;
}

bool getKeyState(SDL_KeyCode code){
	return keyState[code];
}

bool getMouseButtonState(int button){
	return mouseState[button];
}

int getMousePosition(int coord){
	return mousePos[coord];
}

void setMousePosition(int coord, float value){
	mousePos[coord] = value;
}

