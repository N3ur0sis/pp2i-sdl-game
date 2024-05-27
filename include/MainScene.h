/**
 * @file MainScene.h
 * @brief Header file for the main scene.
*/

#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Enemy.h"
#include <Renderer.h>
#include <Inventory.h>

#define NBPARTMAP 4     /**< Number of parts of the map. */


/**
 * @brief Function to create the main scene.
 * 
 * This function creates the main scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void startMainScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to update the main scene.
 * 
 * This function updates the main scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void updateMainScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to unload the main scene.
 * 
 * This function unloads the main scene.
 * 
 * @param scene Pointer to the scene.
 */
void unloadMainScene(Scene* scene);




/**
 * @brief Function to check if p;ayer can insert blue gem (in terms of position).
 * 
 * This function creates the main scene.
 * 
 * @param x X-coordinate of the position.
 * @param y Y-coordinate of the position.
 */
bool canInsertBlueGem(float x, float y);
