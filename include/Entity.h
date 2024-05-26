/**
 * @file Entity.h
 * @brief Header file for the entity component.
*/

#pragma once 
#include <Component.h>
#include <stdlib.h>

#define MAX_COMPONENTS 20   /**< Maximum number of components. */

/**
 * @brief Struct representing an entity.
 * 
 * This struct represents an entity.
 * 
 */
typedef struct _Entity {
    int id;                                 /**< ID of the entity. */
    int componentCount;                     /**< Number of components. */
    Component components[MAX_COMPONENTS];   /**< Array of components. */
} Entity;

/**
 * @brief Function to add a component to an entity.
 * 
 * This function adds a component to an entity.
 * 
 * @param entity Pointer to the entity.
 * @param type Type of the component.
 * @param data Pointer to the data of the component.
 */
void addComponent(Entity* entity, ComponentType type, void* data); 

/**
 * @brief Function to get a component from an entity.
 * 
 * This function gets a component from an entity.
 * 
 * @param entity Pointer to the entity.
 * @param type Type of the component.
 * @return Pointer to the component.
 */
void* getComponent(Entity* entity, ComponentType type);

/**
 * @brief Function to get the animation component from an entity.
 * 
 * This function gets the animation component from an entity.
 * 
 * @param entity Pointer to the entity.
 * @param animationName Name of the animation.
 * @return Pointer to the animation component.
 */
Animation* getAnimationComponent(Entity* entity, const char* animationName);

/**
 * @brief Function to get the distance between two entities.
 * 
 * This function gets the distance between two entities.
 * 
 * @param entity1 Pointer to the first entity.
 * @param entity2 Pointer to the second entity.
 * @return Distance between the entities.
 */
float getDist(Model* object1, Model* object2);