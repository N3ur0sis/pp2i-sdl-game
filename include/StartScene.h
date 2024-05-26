/**
 * @file StartScene.h
 * @brief Header file for the start scene.
*/

#pragma once
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Enemy.h"
#include <Inventory.h>
#include <Marchand.h>

/**
 * @brief Function to create the start scene.
 * 
 * This function creates the start scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void startStartScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to update the start scene.
 * 
 * This function updates the start scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void updateStartScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to unload the start scene.
 * 
 * This function unloads the start scene.
 * 
 * @param scene Pointer to the scene.
 */
void unloadStartScene(Scene* scene);