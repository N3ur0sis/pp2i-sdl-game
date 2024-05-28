/**
 * @file Enemy.h
 * @brief Header file for the enemy component.
*/

#pragma once

#include <Model.h>
#include <Animator.h>
#include <Entity.h>
#include <Scene.h>
#include <Player.h>


/**
 * @brief Struct representing an enemy component.
 * 
 * This struct represents an enemy component.
 * 
 */
typedef struct _EnemyComponent {
    vec3 direction;         /**< Direction of the enemy. */
    float detectionRange;   /**< Detection range of the enemy. */
    float attackRange;      /**< Attack range of the enemy. */
    float movementSpeed;    /**< Movement speed of the enemy. */
    float attackDamage;     /**< Attack damage of the enemy. */
    bool isAttacking;       /**< Boolean flag indicating if the enemy is attacking. */
    bool isAlive;           /**< Boolean flag indicating if the enemy is alive. */
    float health;           /**< Health of the enemy. */
    bool takeDamage;        /**< Boolean flag indicating if the enemy is taking damage. */
    float attackCooldown    /**< Cooldown timer to stop golem from attacking immediately */
} EnemyComponent;

/**
 * @brief Function to create a golem enemy.
 * 
 * This function creates a golem enemy.
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
 * @brief Function to create a purple golem enemy.
 * 
 * This function creates a purple golem enemy.
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
 * @brief Function to handle the logic of the golem enemy.
 * 
 * This function handles the logic of the golem enemy.
 * 
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 * @param golem Pointer to the golem entity.
 * @param player Pointer to the player entity.
 */

Entity* create_skeleton(Scene* scene,float x,float y,float z,float scale);
Entity* create_gobelin(Scene* scene,float x,float y,float z,float scale);

/**
 * @brief Function to update the enemy.
 * 
 * This function updates the enemy.
 * 
 * @param enemy Pointer to the enemy entity.
 * @param player Pointer to the player entity.
 * @param scene Pointer to the scene.
 * @param gameState Pointer to the game state.
 * @param deltaTime Time since the last frame.
 */
void updateEnemy(Entity* enemy, Entity* player, Scene* scene, GameState* gameState, float deltaTime);

/**
 * @brief Function to initialize the enemy component.
 * 
 * This function initializes the enemy component.
 * 
 * @param enemy Pointer to the enemy entity.
 * @param detectionRange Detection range of the enemy.
 * @param attackRange Attack range of the enemy.
 * @param movementSpeed Movement speed of the enemy.
 * @param attackDamage Attack damage of the enemy.
 */
void initializeEnemyComponent(Entity* enemy, float detectionRange, float attackRange, float movementSpeed, float attackDamage);
extern bool isDamageShown;
extern bool isDamageShown;