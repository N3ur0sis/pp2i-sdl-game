/**
* @file Menu.h
* @brief Header file for the pause menu.
* @author VD
*/

#pragma once
#include <Engine.h>

/**
 * @brief Struct representing a menu.
 * 
 * This struct represents a menu.
 * 
 */
typedef struct _Menu {
    char* title;
    int numOptions;
    char** options;
    int selectedOption;
} Menu;

/**
 * @brief Initializes the pause menu.
 * 
 * This function initializes the pause menu.
 * 
 */
Menu* MenuPauseInit();

/**
 * @brief Updates the pause menu.
 * 
 * This function updates the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param menu Pointer to the menu.
 */
void MenuPauseReset(Menu* menu);

/**
 * @brief Moves the selection up in the pause menu.
 * 
 * This function moves the selection up in the pause menu.
 * 
 * @param menu Pointer to the menu.
 */
void MenuPauseUp(Menu* menu);

/**
 * @brief Moves the selection down in the pause menu.
 * 
 * This function moves the selection down in the pause menu.
 * 
 * @param menu Pointer to the menu.
 */
void MenuPauseDown(Menu* menu);

/**
 * @brief Selects an option in the pause menu.
 * 
 * This function selects an option in the pause menu.
 * 
 * @param menu Pointer to the menu.
 * @param gameState Pointer to the game state.
 * @param running Pointer to the running state flag.
 * @param isPaused Pointer to the paused state flag.
 */
void MenuPauseSelect(Menu* menu, GameState* gameState, bool* running, bool* isPaused);

/**
 * @brief Draws the pause menu.
 * 
 * This function draws the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param shaderProgram Pointer to the shader program.
 * @param menu Pointer to the menu.
 */
void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram, Menu* menu);