/**
 * @file Controls.h
 * @brief Input processing functions and definitions for the application.
 * @authors Aymeric ROBERT, Arthur SAUNIER
 */

#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <Time.h>
#include <Event.h>
#include <GameState.h>

#define NB_KEYS 258 /**< Number of keys. */
#define SHIFT 255 /**< Shift key code. */
#define TAB 256 /**< Tab key code. */
#define ESCAPE 257 /**< Escape key code. */
#define PI 3.141592 /**< Value of PI. */

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
void processInput(SDL_Event* e, bool* running, bool* isPaused, GameState* gameState, SceneManager* sceneManager);

/**
 * @brief Handles keyboard key down events.
 * 
 * @param e The SDL event representing the key down.
 */
void handleKeyBoardEventDown(SDL_Event e);

/**
 * @brief Handles keyboard key up events.
 * 
 * @param e The SDL event representing the key up.
 */
void handleKeyBoardEventUp(SDL_Event e);

/**
 * @brief Handles mouse button events.
 * 
 * @param e The SDL event representing the mouse button action.
 */
void handleMouseButtonEvent(SDL_Event e);

/**
 * @brief Gets the state of a specified key.
 * 
 * @param code The SDL key code.
 * @return True if the key is pressed, false otherwise.
 */
bool getKeyState(SDL_Keycode code);

/**
 * @brief Gets the position of the mouse.
 * 
 * @param coord The coordinate to retrieve (0 for x, 1 for y).
 * @return The mouse position in the specified coordinate.
 */
int getMousePosition(int coord);

/**
 * @brief Sets the position of the mouse.
 * 
 * @param coord The coordinate to set (0 for x, 1 for y).
 * @param value The value to set the coordinate to.
 */
void setMousePosition(int coord, float value);

/**
 * @brief Gets the state of a specified mouse button.
 * 
 * @param button The SDL mouse button code.
 * @return True if the button is pressed, false otherwise.
 */
bool getMouseButtonState(int button);

/**
 * @brief Handles mouse wheel events.
 * 
 * @param e The SDL event representing the mouse wheel action.
 */
void handleMouseWheelEvent(SDL_Event e);
void setKeyState(SDL_KeyCode code, bool state);



