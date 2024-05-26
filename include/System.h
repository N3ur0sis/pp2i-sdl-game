/**
 * @file System.h
 * @brief Header file for the system functions.
*/

#pragma once

#include <Scene.h>
#include <Dungeon.h>

/**
 * @brief Function to render the system.
 * 
 * This function renders the system.
 * 
 * @param scene Pointer to the scene.
 * @param gamestate Pointer to the game state.
*/
void renderSystem(Scene* scene, GameState* gamestate);

/**
 * @brief Function to update the system.
 * 
 * This function updates the system.
 * 
 * @param scene Pointer to the scene.
 * @param gamestate Pointer to the game state.
*/
void physicsSystem(Scene* scene);