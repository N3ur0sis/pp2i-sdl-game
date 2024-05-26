/**
 * @file DungeonScene.h
 * @brief Header file for the dungeon scene.
*/

#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include <Dungeon.h>
#include <Enemy.h>

/**
 * @brief Function to create the dungeon scene.
 * 
 * This function creates the dungeon scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void DungeonMainScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to update the dungeon scene.
 * 
 * This function updates the dungeon scene.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 */
void updateDungeonScene(Scene* scene, GameState* gameState);

/**
 * @brief Function to unload the dungeon scene.
 * 
 * This function unloads the dungeon scene.
 * 
 * @param scene Pointer to the scene.
 */
void unloadDungeonScene(Scene* scene);