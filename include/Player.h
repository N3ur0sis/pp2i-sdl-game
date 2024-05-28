/**
 * @file Player.h
 * @brief Header file for the player component.
*/

#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <SceneManager.h>
#include <Controls.h>
#include <Objects.h>

#define DAMAGE 50.0f        /**< Damage of the player. */
#define ATTACK_RANGE 2.5f   /**< Attack range of the player. */

/**
 * @brief Linearly interpolates between two vectors.
 * 
 * This function linearly interpolates between two vectors.
 * 
 * @param a First vector.
 * @param b Second vector.
 * @param res Resulting vector.
 * @param t Interpolation factor.
 */
void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);

/**
 * @brief Function to move the player.
 * 
 * This function moves the player based on the input and the camera.
 * 
 * @param player Pointer to the player entity.
 * @param deltaTime Time since the last frame.
 * @param camera Pointer to the camera.
 */
void playerMovement(Entity* player, float deltaTime, Camera* camera);

/**
 * @brief Updates the player's animator based on the current state and input.
 * 
 * This function manages the animation state of the player entity, ensuring that the correct
 * animation is played based on the player's actions, such as moving, attacking, or being idle.
 * 
 * @param playerEntity Pointer to the player entity.
 * @param gameState Pointer to the game state.
 */
void updatePlayerAnimator(Entity* playerEntity, GameState* gameState);

/**
 * @brief Moves the camera to follow the player.
 * 
 * This function moves the camera to follow the player, ensuring that the camera is always
 * positioned behind the player and looking at the player.
 * 
 * @param camera Pointer to the camera.
 * @param position Position of the player.
 * @param targetPosition Target position of the player.
 * @param deltaTime Time since the last frame.
 */
void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime);

/**
 * @brief Linearly interpolates between two floats.
 * 
 * This function linearly interpolates between two floats.
 * 
 * @param a First float.
 * @param b Second float.
 * @param t Interpolation factor.
 * @return Result of the interpolation.
 */
float lerp_float(float a, float b, float t);

/**
 * @brief Linearly interpolates the camera position and yaw.
 * 
 * This function linearly interpolates the camera position and yaw.
 * 
 * @param camera Pointer to the camera.
 * @param old_pos Old position of the camera.
 * @param new_pos New position of the camera.
 * @param old_yaw Old yaw of the camera.
 * @param new_yaw New yaw of the camera.
 * @param steps Number of steps to interpolate.
 * @param duration Duration of the interpolation.
 */
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration);

/**
 * @brief Function to check if the player is interacting.
 * 
 * This function checks if the player is interacting.
 * 
 * @return True if the player is interacting, false otherwise.
 */
bool playerInteract();

/**
 * @brief Function to check if the player is dead.
 * 
 * This function checks if the player is dead.
 * 
 * @param gamestate Pointer to the game state.
 */
void checkDead(GameState* gamestate);

/**
 * @brief Function to damage the player.
 * 
 * This function damages the player.
 * 
 * @param gamestate Pointer to the game state.
 * @param damage Amount of damage to deal to the player.
 */
void damagePlayer(GameState* gamestate, int damage);

/**
 * @brief Function to create the player entity.
 * 
 * This function creates the player entity.
 * 
 * @param scene Pointer to the scene.
 * @param x X position of the player.
 * @param y Y position of the player.
 * @param z Z position of the player.
 * @return Pointer to the player entity.
 */
Entity* create_player(Scene*  scene,float x,float y,float z);

/**
 * @brief Function to create the player's sword entity.
 * 
 * This function creates the player's sword entity.
 * 
 * @param scene Pointer to the scene.
 * @param parent Pointer to the parent entity.
 * @return Pointer to the sword entity.
 */
Entity* create_sword(Scene* scene,Entity* parent);

/**
 * @brief Function to make the player attack.
 * 
 * This function makes the player attack.
 * 
 * @param player Pointer to the player entity.
 * @param enemy Pointer to the enemy entity.
 * @param gameState Pointer to the game state.
 */
void player_attack(Entity* player,Entity* enemy,GameState* gameState);

/**
 * @brief Function to play the sound of the player.
 * 
 * This function plays the sound of the player.
 * 
 * @param player Pointer to the player entity.
 * @param gamestate Pointer to the game state.
 */
void playSoundPlayer(Entity* player,GameState* gamestate);
void drawHUD(Scene* scene, GameState* gamestate);
void heal(GameState* gameState, Inventory* inventory, bool* is_Healing);