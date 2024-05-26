/**
 * @file Ennemy.h
 * @brief Header file for the enemy component.
*/

#pragma once

#include <Model.h>
#include <Animator.h>
#include <Entity.h>
#include <Scene.h>

/**
 * @brief Function to create a golem.
 * 
 * This function creates a golem.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the golem.
 * @param y Y position of the golem.
 * @param z Z position of the golem.
 * @param scale Scale of the golem.
 * @return Pointer to the golem entity.
*/
Entity *create_golem(Scene* scene,float x,float y,float z,float scale);

/**
 * @brief Function to create a blue golem.
 * 
 * This function creates a blue golem.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the golem.
 * @param y Y position of the golem.
 * @param z Z position of the golem.
 * @param scale Scale of the golem.
 * @return Pointer to the golem entity.
*/
Entity* create_golemBlue(Scene* scene,float x,float y,float z,float scale);

/**
 * @brief Function to create a purple golem.
 * 
 * This function creates a purple golem.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the golem.
 * @param y Y position of the golem.
 * @param z Z position of the golem.
 * @param scale Scale of the golem.
 * @return Pointer to the golem entity.
*/
Entity* create_golemPurple(Scene* scene,float x,float y,float z,float scale);

/**
 * @brief Function to handle the logic of the golem.
 * 
 * This function handles the logic of the golem.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 * @param golem Pointer to the golem entity.
 * @param player Pointer to the player entity.
*/
void golemLogic(Scene* scene,GameState* gameState,Entity* golem,Entity* player);

/**
 * @brief Function to create a gobelin.
 * 
 * This function creates a gobelin.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the gobelin.
 * @param y Y position of the gobelin.
 * @param z Z position of the gobelin.
 * @param scale Scale of the gobelin.
 * @return Pointer to the gobelin entity.
*/
Entity* create_gobelin(Scene* scene,float x,float y,float z,float scale);

/**
 * @brief Function to create a skeleton.
 * 
 * This function creates a skeleton.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the skeleton.
 * @param y Y position of the skeleton.
 * @param z Z position of the skeleton.
 * @param scale Scale of the skeleton.
 * @return Pointer to the skeleton entity.
*/
Entity* create_skeleton(Scene* scene,float x,float y,float z,float scale);