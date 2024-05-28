/**
 * @file GameState.h
 * @brief Header file for the game state.
*/

#pragma once
#include <Inventory.h>

typedef struct _Menu Menu;

/**
 * @brief Struct representing the game state.
 * 
 * This struct represents the game state.
 * 
 */
typedef struct GameState {
    bool enemyIsAttacking;          /**< Boolean flag indicating if the enemy is attacking. */
    bool playerIsAttacking;         /**< Boolean flag indicating if the player is attacking. */
    float max_health;               /**< Maximum health of the player. */
    float playerHealth;             /**< Health of the player. */
    Inventory* inventory;           /**< Pointer to the player's inventory. */
    Inventory* marchantInventory;   /**< Pointer to the marchant's inventory. */
    int g_WindowWidth;              /**< Width of the window. */
    int g_WindowHeight;             /**< Height of the window. */
    bool isPlayerDead;              /**< Boolean flag indicating if the player is dead. */
    int nextSceneIndex;             /**< Index of the next scene. */
    int currentSceneIndex;          /**< Index of the current scene. */
    int previousSceneIndex;         /**< Index of the previous scene. */
    bool change;                    /**< Boolean flag indicating if the scene is changing. */
    bool isForestDungeonDone;       /**< Boolean flag indicating if the forest dungeon is done. */
    Menu* pauseMenu;                /**< Pointer to the pause menu. */
    bool restarting;                /**< Boolean flag indicating if the game is restarting. */
    bool mainMenuOpen;              /**< Boolean flag indicating if the main menu is open. */
    int money;                      /**< Money of the player. */
    bool fullscreen;                /**< Boolean flag indicating if the game is in fullscreen mode. */
    // Add other game state variables as needed
} GameState;