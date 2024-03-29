#include <Controls.h>
#include <math.h>


//State of Mouse and keyboard input
char keyState[NB_KEYS] = { 0 };
float mousePos[6] = {0}; // 0->posX 1->posY 2->lastX 3->lastY 4->wheely ->5 lastWheelY
char mouseState[5] = { 0 }; // mouse button state


void processInput(SDL_Event* e,  bool* running){

	
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
	}
}

void handleKeyBoardEventDown(SDL_Event e){
	if (e.key.keysym.scancode == SDL_SCANCODE_LSHIFT || e.key.keysym.scancode == SDL_SCANCODE_RSHIFT){
		keyState[255] = 1;
	} else if (e.key.keysym.scancode == SDL_SCANCODE_TAB) {
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

void treatMovingInput(vec3 position, vec3 rotation){
	float speed = 0.002f;
	float speedDiag = speed / sqrt(2);

	float realSpeed = 0.003f;
	float realSpeedDiag = realSpeed / sqrt(2);
	float x = position[0];
	float y = position[1];
	float z = position[2];
	float xRot = rotation[0];
	float yRot = rotation[1];
	float zRot = rotation[2];

	if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_d)) && (getKeyState(SHIFT))) {
		z += realSpeedDiag;
		x -= realSpeedDiag;
	}
	else if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_q)) && (getKeyState(SHIFT))) {
		z += realSpeedDiag;
		x += realSpeedDiag;
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_d)) && (getKeyState(SHIFT))) {
		z -= realSpeedDiag;
		x -= realSpeedDiag;
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_q)) && (getKeyState(SHIFT))) {
		z -= realSpeedDiag;
		x += realSpeedDiag;
	}
	if ((getKeyState(SDLK_z)) && (getKeyState(SHIFT))){
		z += realSpeed;
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SHIFT))){
		z -= realSpeed;
	}
	else if ((getKeyState(SDLK_q)) && (getKeyState(SHIFT))){
		x += realSpeed;
	}
	else if ((getKeyState(SDLK_d)) && (getKeyState(SHIFT))){
		x -= realSpeed;
	}
	else if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_d))) {
		z += speedDiag;
		x -= speedDiag;
	}
	else if ((getKeyState(SDLK_z)) && (getKeyState(SDLK_q))) {
		z += speedDiag;
		x += speedDiag;
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_d))) {
		z -= speedDiag;
		x -= speedDiag;
	}
	else if ((getKeyState(SDLK_s)) && (getKeyState(SDLK_q))) {
		z -= speedDiag;
		x += speedDiag;
	}
	else if (getKeyState(SDLK_z)){
		z += speed;
	}
	else if (getKeyState(SDLK_s)){
		z -= speed;
		zRot += 0.1;
	}
	else if (getKeyState(SDLK_q)){
		x += speed;
	}
	else if (getKeyState(SDLK_d)){
		x -= speed;
	}
	position[0] = x;
	position[1] = y;
	position[2] = z;
	rotation[0] = xRot;
	rotation[1] = yRot;
	rotation[2] = zRot;
}