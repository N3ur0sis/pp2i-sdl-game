/**
 * @file Component.h
 * @brief Component header file
*/

#pragma once

#include <Animator.h>
#include <Light.h>
#include <Collider.h>

/**
 * @brief Enum representing the type of a component.
 * 
 * This enum represents the type of a component.
*/
typedef enum {
    COMPONENT_RENDERABLE,   /**< Renderable component */
    COMPONENT_ANIMATION,    /**< Animation component */
    COMPONENT_ANIMATOR,    /**< Animator component */
    COMPONENT_COLLIDER,    /**< Collider component */
    COMPONENT_LIGHT,        /**< Light component */
    COMPONENT_ATTACHMENT,   /**< Attachment component */
    COMPONENT_RIGIDBODY,    /**< RigidBody component */
    COMPONENT_DUNGEON,    /**< Dungeon component */
    COMPONENT_HEALTH,   /**< Health component */
    COMPONENT_DAMAGE,   /**< Damage component */
    COMPONENT_ENEMY,    /**< Enemy component */
    COMPONENT_PLAYER    /**< Player component */
} ComponentType;

/**
 * @brief Structure representing a component.
 * 
 * This structure represents a component.
*/
typedef struct _Component{
    ComponentType type; /**< Type of the component */
    void* data;     /**< Data of the component */
} Component;

/**
 * @brief Structure representing an attachment component.
 * 
 * This structure represents an attachment component.
*/
typedef struct {
    int boneIndex;       /**< Index of the bone to which the model is attached */
    Model* parentModel;         /**< Parent model */
    Animator* parentAnimator;   /**< Parent animator */
    vec3 offsetPosition; /**< Offset position relative to the bone */
    vec3 offsetRotation; /**< Offset rotation relative to the bone */
    vec3 offsetScale;    /**< Offset scale relative to the bone */
} AttachmentComponent;

/**
 * @brief Structure representing a rigid body.
 * 
 * This structure represents a rigid body.
*/
typedef struct {
    vec3 velocity;  /**< Velocity of the rigid body */
    float speed;    /**< Speed of the rigid body */
} RigidBody;

/**
 * @brief Free the attachment component.
 * 
 * This function frees the attachment component.
 * 
 * @param AttachmentComponent The attachment component to free.
*/
void FreeAttachementComponent(AttachmentComponent* AttachmentComponent);

/**
 * @brief Free the rigid body.
 * 
 * This function frees the rigid body.
 * 
 * @param RigidBody The rigid body to free.
*/
void FreeRigidBody(RigidBody* rb);

/**
 * @brief Structure representing a player component.
 * 
 * This structure represents a player component.
*/
typedef struct _PlayerComponent {
    bool isAttacking;   /**< Is the player attacking */
    bool isAlive;       /**< Is the player alive */
    bool hasWeapon;     /**< Does the player have a weapon */
    float currentHealth;    /**< Current health of the player */
    float maxHealth;        /**< Maximum health of the player */
    float attackDamage;     /**< Attack damage of the player */
    float attackRange;      /**< Attack range of the player */
} PlayerComponent;