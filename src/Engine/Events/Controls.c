#include <Controls.h>
#include <math.h>

//State of Mouse and keyboard input
char keyState[NB_KEYS] = { 0 };
float mousePos[6] = {0}; // 0->posX 1->posY 2->lastX 3->lastY 4->wheely ->5 lastWheelY
char mouseState[5] = { 0 }; // mouse button state


void processInput(SDL_Event* e,  bool* running, GameState* gameState){

	
	switch (e->type){
		case SDL_QUIT:
			*running = false;
			break;
		case SDL_KEYDOWN:
			handleKeyBoardEventDown(*e);
			break;
		case SDL_KEYUP:
			handleKeyBoardEventUp(*e);
			break;
		case SDL_MOUSEMOTION:
			mousePos[0] = e->motion.x;
			mousePos[1] = e->motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			handleMouseButtonEvent(*e);
            break;
		case SDL_MOUSEBUTTONUP:
			handleMouseButtonEvent(*e);
			break;
		case SDL_MOUSEWHEEL:
			handleMouseWheelEvent(*e);
		case SDL_WINDOWEVENT:
        	if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
            	printf("MESSAGE:Resizing window...\n");
            	gameState->g_WindowWidth = e->window.data1;
				gameState->g_WindowHeight = e->window.data2;
        		}
        break;
	}
}

void handleKeyBoardEventDown(SDL_Event e){
	if (e.key.keysym.scancode == SDL_SCANCODE_LSHIFT || e.key.keysym.scancode == SDL_SCANCODE_RSHIFT){
		keyState[255] = 1;
	} else if (e.key.keysym.scancode == SDL_SCANCODE_TAB) {
		keyState[256] = 1;
	} else if (e.key.keysym.sym == SDLK_ESCAPE) {
		keyState[256] = 1;
	} else if (e.key.keysym.sym < 255) {
		keyState[e.key.keysym.sym] = e.key.state;
	}
}

void handleKeyBoardEventUp(SDL_Event e){
	if (e.key.keysym.scancode == SDL_SCANCODE_LSHIFT || e.key.keysym.scancode == SDL_SCANCODE_RSHIFT){ 
		keyState[255] = 0;
	} else if (e.key.keysym.scancode == SDL_SCANCODE_TAB) {
		keyState[256] = 0;
	} else if (e.key.keysym.sym == SDLK_ESCAPE) {
		keyState[256] = 0;
	} else if (e.key.keysym.sym < 255) {
		keyState[e.key.keysym.sym] = e.key.state;
	}
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
