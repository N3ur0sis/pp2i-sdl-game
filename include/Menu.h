/*
* Menu.h
* Header file for the pause menu.
* Authors: VD
*/

#pragma once
#include <Engine.h>

/**
 * @brief Draws the pause menu.
 * 
 * This function draws the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param shaderProgram Pointer to the shader program.
 */
void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram);