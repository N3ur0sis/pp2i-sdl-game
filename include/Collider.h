/**
* @file Collider.h
* @brief Collider header file
*/

#pragma once
#include <Model.h>

#define MAXCOLLIDER 3000    /**< Maximum number of colliders */

/**
 * @brief Structure representing a collider.
 * 
 * This structure represents a collider.
*/
typedef struct _Collider{
    vec3 boundingBoxReference[MAXCOLLIDER][2];  /**< Reference bounding box */
    vec3 boundingBox[MAXCOLLIDER][2];           /**< Bounding box */
    mat4 transformMatrix;                       /**< Transformation matrix */
    int numCollider;                            /**< Number of colliders */
    bool isCollidable;                          /**< Is collidable */
} Collider;

/**
 * @brief Creates a new Collider instance.
 * 
 * @param path The path to the model file.
 * @return Pointer to the created Collider instance or NULL on failure.
 */
Collider* ColliderCreate(char* path);

/**
 * @brief Updates the collider.
 * 
 * This function updates the collider.
 * 
 * @param collider The collider to update.
 */
void UpdateCollider(Collider* collider);

/**
 * @brief Frees the collider.
 * 
 * This function frees the collider.
 * 
 * @param collider The collider to free.
 */
void FreeCollider(Collider* collider);