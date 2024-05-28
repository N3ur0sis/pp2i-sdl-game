/**
 * @file Marchand.h
 * @brief Header file for the marchand component.
*/

#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Enemy.h"
#include <Renderer.h>

/**
 * @brief Function to create a marchand.
 * 
 * This function creates a marchand.
 * 
 * @param scene Pointer to the scene.
 * @param position Position of the marchand.
 * @param scale Scale of the marchand.
 * @param rotation Rotation of the marchand.
 * @return Pointer to the marchand entity.
*/
Entity* createMarchand(Scene* scene, vec3 position, vec3 scale, vec3 rotation);

/**
 * This function creates a cariolle.
 * 
 * @param scene Pointer to the scene.
 * @param position Position of the marchand.
 * @param scale Scale of the marchand.
 * @param rotation Rotation of the marchand.
 * @return Pointer to the marchand entity.
*/
Entity* createCariolle(Scene* scene, vec3 position, vec3 scale, vec3 rotation);



/**
 * @brief Function when the player is talking to the marchand.
 * 
 * This function is called when the player is talking to the marchand.
 * 
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @param shader Shader of the game.
 * @param click_counter Counter of clicks.
 * @param is_clicking Pointer to the clicking state.
 * @param isBusy Pointer to the busy state.
*/
void talkToMarchandStart(float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy);

/**
 * @brief Function when the player is talking to the marchand.
 * 
 * This function is called when the player is talking to the marchand.
 * 
 * @param inventory Pointer to the inventory of the player.
 * @param marchantInventory Pointer to the inventory of the marchand.
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @param shader Shader of the game.
 * @param click_counter Counter of clicks.
 * @param is_clicking Pointer to the clicking state.
 * @param isBusy Pointer to the busy state.
 * @param money Pointer to the money of the player.
*/
void talkToMarchandMain(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy, int* money, bool* hasBoughtTorch);

/**
 * @brief Function to trade with the marchand.
 * 
 * This function is called when the player is trading with the marchand.
 * 
 * @param inventory Pointer to the inventory of the player.
 * @param marchantInventory Pointer to the inventory of the marchand.
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @param shader Shader of the game.
 * @param click_counter Counter of clicks.
 * @param is_clicking Pointer to the clicking state.
 * @param isBusy Pointer to the busy state.
 * @param money Pointer to the money of the player.
*/
void tradingWithMarchand(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader,int* click_counter, bool* is_clicking, bool* isBusy, int* money, bool* hasBoughtTorch);

/**
 * @brief Function to check if the player wants to trade.
 * 
 * This function checks if the player wants to trade.
 * 
 * @param x X position of the mouse.
 * @param y Y position of the mouse.
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @return Boolean value indicating if the player wants to trade.
*/
bool checkWantToTrade(int x, int y, float window_width, float window_height);