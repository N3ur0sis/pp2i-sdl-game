/**
 * @file Dungeon.h
 * @brief Dungeon header file
*/

#pragma once

#include <Room.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "List.h"
#include <stdbool.h>
#include <string.h>
#include <GameState.h>
#include <Scene.h>
#include <Controls.h>
#define NB_ROOM_MAX 15
#define NB_ROOM_MIN 10
#define MIN_DOOR 1
#define MAX_DOOR 4
#define NB_MODEL_SALLE 8
#define ChangeTime 2000.0f
#define LootChance 3;
#define FightChance 2;

typedef struct _Dungeon Dungeon;

/**
 * @brief Structure representing a dungeon.
 * 
 * This structure represents a dungeon.
*/
struct  _Dungeon
{
    Room* rooms;                /**< Rooms */
    L_Room* type_room;          /**< Type of rooms */
    char **adj;                 /**< Adjacency list */
    char direction;             /**< Direction */
    char previous_direction;    /**< Previous direction */
    int nb_rooms;               /**< Number of rooms */
    int current_room;           /**< Current room */
    int previous_room;          /**< Previous room */
    int nb_enemy;               /**< Number of enemies */
    bool change;                /**< Change */
    bool hasKey;                /**< If the player has the key */
    bool quit;                  /**< Quit */
    float lastRoomChangeTime;   /**< Last room change time */

    
};

/**
 * @brief Creates a new Dungeon instance.
 * 
 * @return Pointer to the created Dungeon instance or NULL on failure.
 */
Dungeon* dj_create();

/**
 * @brief Frees the dungeon.
 * 
 * This function frees the dungeon.
 * 
 * @param dj The dungeon
*/
void freeDungeon(Dungeon *dj);

/**
 * @brief Frees the type of rooms.
 *  
 * This function frees the type of rooms.
 * 
 * @param dj The dungeon
 */
void freeTypeRooms(Dungeon* dj);

/**
 * @brief Initializes the dungeon.
 * 
 * This function initializes the dungeon.
 * 
 * @param dj The dungeon
 */
void initialize(Dungeon *dj);

/**
 * @brief Initialize the adjacency list
 * 
 * This function initializes the adjacency list of the dungeon.
 * 
 * @param dj The dungeon
 */
void initializeAdjacencyList(Dungeon *dj);

/**
 * @brief Free the adjacency list
 * 
 * This function frees the adjacency list of the dungeon.
 * 
 * @param dj The dungeon
 */
void freeAdjacencyList(Dungeon *dj);

/**
 * @brief Print the adjacency list
 * 
 * This function prints the adjacency list of the dungeon.
 * 
 * @param dj The dungeon
 */
void printAdjList(Dungeon *dj);

/**
 * @brief Initialize the rooms
 * 
 * This function initializes the rooms of the dungeon.
 * 
 * @param dj The dungeon
 */
void initializeRooms(Dungeon *dj);

/**
 * @brief Free the rooms
 * 
 * This function frees the rooms of the dungeon.
 * 
 * @param dj The dungeon
 */
void freeRooms(Dungeon* dj);

/**
 * @brief prints the information of the dungeon
 * 
 * This function prints the information of the dungeon.
 * 
 * @param dj The Dungeon object
*/
void Affiche(Dungeon *dj);

/**
 * @brief Find the maximum of a list of integers
 * 
 * This function finds the maximum of a list of integers.
 * 
 * @param list The list of integers
 * @param size The size of the list
 * @return int The maximum of the list
 */
int maxList(int list[], int size);

/**
 * @brief Find the maximum of two integers
 * 
 * This function finds the maximum of two integers.
 * 
 * @param a The first integer
 * @param b The second integer
 * @return int The maximum of the two integers
 */
int max(int a, int b);


void depthFirstSearch(Dungeon *dj, int room, int depth, int *depths, int *visited);

/**
 * @brief Find the depth of each room
 * 
 * This function finds the depth of each room.
 * 
 * @param dj The dungeon
 * @return int* The depth of each room
 */
int *profondeur(Dungeon *dj);

/**
 * @brief Print the depth of each room
 * 
 * This function prints the depth of each room in the dungeon.
 * 
 * @param depths The depth of each room
 * @param nb_rooms The number of rooms
 */
void printDepth(int *depths, int nb_rooms);

/**
 * @brief Load the room
 * 
 * This function loads the room.
 * 
 * @param scene The scene
 * @param player The player
 * @param dj The Dungeon object
 * @param body The RigidBody
 * @param collider The Collider
 * @param gameState The GameState
 */
void LoadRoom(Scene* scene,Model* player, Dungeon* dj,RigidBody* body, Collider* collider,GameState* gameState);

/**
 * @brief Load the room 1C
 * 
 * This function loads the room 1C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom1C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 2C
 * 
 * This function loads the room 2C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 3C
 * 
 * This function loads the room 3C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom3C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 2I
 * 
 * This function loads the room 2I.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2I(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 3T
 * 
 * This function loads the room 3T.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom3T(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 2L
 * 
 * This function loads the room 2L.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom2L(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
 * @brief Load the room 4C
 * 
 * This function loads the room 4C.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoom4C(Scene* scene,GameState* gameState,Model* player,Dungeon*dj,RigidBody* body);

/**
 * @brief Load the room B
 * 
 * This function loads the room B.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param map The Model
 * @param col The Collider
 * @param player The Model
 * @param dj The Dungeon object
 * @param body The RigidBody
 */
void LoadRoomB(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);

/**
* @brief Handle the logic of the room 1C
*
* This function handles the logic of the room 1C.
*
* @param scene The scene
* @param gameState The GameState
* @param dj The Dungeon object
* @param body The RigidBody
*/
void LogicRoom1C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
* @brief Handle the logic of the room 2C
*
* This function handles the logic of the room 2C.
*
* @param scene The scene
* @param gameState The GameState
* @param dj The Dungeon object
* @param body The RigidBody
*/
void LogicRoom2C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
* @brief Handle the logic of the room 3C
*
* This function handles the logic of the room 3C.
*
* @param scene The scene
* @param gameState The GameState
* @param dj The Dungeon object
* @param body The RigidBody
*/
void LogicRoom3C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
* @brief Handle the logic of the room 4C
*
* This function handles the logic of the room 4C.
*
* @param scene The scene
* @param gameState The GameState
* @param dj The Dungeon object
* @param body The RigidBody
*/
void LogicRoom4C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
 * @brief Handle the logic of the room 2L
 * 
 * This function handles the logic of the room 2L.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
*/
void LogicRoom2L (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
 * @brief Handle the logic of the room 2I
 * 
 * This function handles the logic of the room 2I.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
*/
void LogicRoom2I (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
 * @brief Handle the logic of the room 3T
 * 
 * This function handles the logic of the room 3T.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
*/
void LogicRoom3T (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
 * @brief Handle the logic of the room B
 * 
 * This function handles the logic of the room B.
 * 
 * @param scene The scene
 * @param gameState The GameState
 * @param dj The Dungeon object
 * @param body The RigidBody
*/
void LogicRoomB (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );

/**
 * @brief Initialize the LRooms
 * 
 * This function initializes the LRooms.
 * 
 * @param dj The Dungeon object
 * 
*/
void initializeLRooms(Dungeon *dj);

/**
 * @brief Set the type of rooms
 * 
 * This function sets the type of rooms.
 * 
 * @param dj The Dungeon object
*/
void setTypeRoom(Dungeon* dj);

/**
* @brief Display the minimap
*
* This function displays the minimap.
*
* @param scene The scene
* @param dj The Dungeon object
* @param gameState The GameState
*/
void displayMiniMap(Scene* scene, Dungeon* dj,GameState* gameState);