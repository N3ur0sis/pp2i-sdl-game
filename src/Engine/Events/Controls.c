/**
 * @file Controls.c
 * @brief Implementation of input processing functions for the application.
 * @authors Aymeric ROBERT, Arthur SAUNIER, VD
 */

#include "Controls.h"

/* State of mouse and keyboard input */
static char keyState[NB_KEYS] = { 0 };
static float mousePos[6] = { 0 }; /* 0=posX ; 1=posY ; 2 = lastX ; 3 = lastY ; 4 = wheelY ; 5 = lastWheelY */
static char mouseState[5] = { 0 }; /* Mouse button State : 1 = Left Click ; . . . */

/**
 * @brief Logs an SDL error message.
 * 
 * @param msg The error message to log.
 */
static void logSDLError(const char* msg) {
    fprintf(stderr, "ERROR: %s: %s\n", msg, SDL_GetError());
}

/**
 * @brief Processes the input events.
 * 
 * This function processes input events, updates the running state, game state, and scene manager.
 * 
 * @param e Pointer to the SDL event.
 * @param running Pointer to the running state flag.
 * @param isPaused Pointer to the paused state flag.
 * @param gameState Pointer to the current game state.
 * @param sceneManager Pointer to the scene manager.
 */
void processInput(SDL_Event* e, bool* running, bool* isPaused, GameState* gameState, SceneManager* sceneManager) {
    switch (e->type) {
        case SDL_QUIT:
            *running = false;
            break;
        case SDL_KEYDOWN:
			/*Handle pause menu input*/
			if (e->key.keysym.sym == SDLK_ESCAPE){
				*isPaused = !*isPaused;
                MenuPauseReset(gameState->pauseMenu);
            } else if(*isPaused){
                if (e->key.keysym.sym == SDLK_DOWN) {
                    MenuPauseDown(gameState->pauseMenu);
                } else if (e->key.keysym.sym == SDLK_UP) {
                    MenuPauseUp(gameState->pauseMenu);
                } else if (e->key.keysym.sym == SDLK_RETURN) {
                    MenuPauseSelect(gameState->pauseMenu, gameState, running, isPaused);
                }
            }
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
            break;
        case SDL_WINDOWEVENT:
            if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
                gameState->g_WindowWidth = e->window.data1;
                gameState->g_WindowHeight = e->window.data2;
            }
            break;
        case CHANGE_SCENE_EVENT:
            if (sceneManager) {
                HandleChangeScene(sceneManager);
            }
            break;
        default:
            break;
    }
}

/**
 * @brief Handles keyboard key down events.
 * 
 * @param e The SDL event representing the key down.
 */
void handleKeyBoardEventDown(SDL_Event e) {
    SDL_Scancode scancode = e.key.keysym.scancode;
    if (scancode == SDL_SCANCODE_LSHIFT || scancode == SDL_SCANCODE_RSHIFT) {
        keyState[SHIFT] = 1;
    } else if (scancode == SDL_SCANCODE_TAB) {
        keyState[TAB] = 1;
    } else if (e.key.keysym.sym == SDLK_ESCAPE) {
        keyState[ESCAPE] = 1;
    } else if (e.key.keysym.sym < NB_KEYS) {
        keyState[e.key.keysym.sym] = e.key.state;
    }
}

/**
 * @brief Handles keyboard key up events.
 * 
 * @param e The SDL event representing the key up.
 */
void handleKeyBoardEventUp(SDL_Event e) {
    SDL_Scancode scancode = e.key.keysym.scancode;
    if (scancode == SDL_SCANCODE_LSHIFT || scancode == SDL_SCANCODE_RSHIFT) {
        keyState[SHIFT] = 0;
    } else if (scancode == SDL_SCANCODE_TAB) {
        keyState[TAB] = 0;
    } else if (e.key.keysym.sym == SDLK_ESCAPE) {
        keyState[ESCAPE] = 0;
    } else if (e.key.keysym.sym < NB_KEYS) {
        keyState[e.key.keysym.sym] = e.key.state;
    }
}

/**
 * @brief Handles mouse button events.
 * 
 * @param e The SDL event representing the mouse button action.
 */
void handleMouseButtonEvent(SDL_Event e) {
    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
        mouseState[e.button.button] = e.button.state;
    } else {
        logSDLError("Invalid mouse button event");
    }
}

/**
 * @brief Handles mouse wheel events.
 * 
 * @param e The SDL event representing the mouse wheel action.
 */
void handleMouseWheelEvent(SDL_Event e) {
    mousePos[4] += e.wheel.y;
}

/**
 * @brief Gets the state of a specified key.
 * 
 * @param code The SDL key code.
 * @return True if the key is pressed, false otherwise.
 */
bool getKeyState(SDL_Keycode code) {
    if (code < 0 || code >= NB_KEYS) {
        logSDLError("Invalid key code");
        return false;
    }
    return keyState[code];
}

/**
 * @brief Gets the state of a specified mouse button.
 * 
 * @param button The SDL mouse button code.
 * @return True if the button is pressed, false otherwise.
 */
bool getMouseButtonState(int button) {
    if (button < 0 || button >= sizeof(mouseState)) {
        logSDLError("Invalid mouse button code");
        return false;
    }
    return mouseState[button];
}

/**
 * @brief Gets the position of the mouse.
 * 
 * @param coord The coordinate to retrieve (0 for x, 1 for y).
 * @return The mouse position in the specified coordinate.
 */
int getMousePosition(int coord) {
    if (coord < 0 || coord >= sizeof(mousePos) / sizeof(mousePos[0])) {
        logSDLError("Invalid mouse position coordinate");
        return -1;
    }
    return mousePos[coord];
}

/**
 * @brief Sets the position of the mouse.
 * 
 * @param coord The coordinate to set (0 for x, 1 for y).
 * @param value The value to set the coordinate to.
 */
void setMousePosition(int coord, float value) {
    if (coord < 0 || coord >= sizeof(mousePos) / sizeof(mousePos[0])) {
        logSDLError("Invalid mouse position coordinate");
        return;
    }
    mousePos[coord] = value;
}

/**
 * @brief Sets the state of a specified key.
 * 
 * @param code The SDL key code.
 * @param state The state to set the key to.
 */
void setKeyState(SDL_KeyCode code, bool state){
	keyState[code] = state;
}
