/**
 * @file Room.h
 * @brief Header file for the room component.
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Model.h>
#include <Component.h>

#define NB_ENEMY 5  /**< Maximum number of enemies. */

typedef struct _Room Room;

/**
 * @brief Struct representing a room.
 * 
 * This struct represents a room.
 * 
 */
struct  _Room
{
    int* data;                  /**< Data of the room. */
    int nb_door;                /**< Number of doors in the room. */
    int id;                     /**< ID of the room. */
    int type;                   /**< Type of the room. */
    bool isCompleted;           /**< Boolean flag indicating if the room is completed. */
    int nb_enemy;               /**< Number of enemies in the room. */
    int id_enemy[NB_ENEMY];     /**< Array of enemy IDs. */
};

/**
 * @brief Struct representing a L room.
 * 
 * This struct represents a L room.
 */
typedef struct _L_Room {
    Model* model;       /**< Model of the room. */
    Collider* col;      /**< Collider of the room. */
}L_Room;

/**
 * @brief Function to free a room.
 * 
 * This function frees a room.
 * 
 * @param room Pointer to the room.
 */
void freeRoom(Room* room);

/**
 * @brief Function to free a L room.
 * 
 * This function frees a L room.
 * 
 * @param l Pointer to the L room.
 */
void freeLRoom(L_Room* l);

/**
 * @brief Function to initialize a room.
 * 
 * This function initializes a room.
 * 
 * @param room Pointer to the room.
 */
void initializeRoom(Room* room);

/**
 * @brief Function to initialize a Boss room.
 * 
 * This function initializes a Boss room.
 * 
 * @param room Pointer to the room.
 */
void initializeBossRoom(Room *room);

/**
 * @brief Function to initialize a Loot room.
 * 
 * This function initializes a Loot room.
 * 
 * @param room Pointer to the room.
 */
void initializeLootRoom(Room *room);

/**
 * @brief Function to initialize a Fight room.
 * 
 * This function initializes a Fight room.
 * 
 * @param room Pointer to the room.
 */
void initializeFightRoom(Room *room);

