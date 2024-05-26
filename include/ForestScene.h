/**
 * @file ForestScene.h
 * @brief Header file for the forest scene.
*/

#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include <Enemy.h>
#define FLAMEDIST 2.0f

/**
 * @brief Function to create the forest scene.
 * 
 * This function creates the forest scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void ForestMainScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to update the forest scene.
 * 
 * This function updates the forest scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void updateForestScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to unload the forest scene.
 * 
 * This function unloads the forest scene.
 * 
 * @param scene Pointer to the scene.
 */
void unloadForestScene(Scene* scene);