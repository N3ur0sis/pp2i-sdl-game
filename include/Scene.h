/**
 * @file Scene.h
 * @brief Header file for the scene component.
*/

#pragma once

#include <Shader.h>
#include <Skybox.h>
#include <Entity.h>
#include <GameState.h>
#include <SDL_mixer.h>

#define MAX_ENTITIES 100    /**< Maximum number of entities. */

#define INIT_SCENE(sceneVar, sceneManager, startFunc, updateFunc, unloadFunc) \     
    Scene* sceneVar = (Scene*)calloc(1, sizeof(Scene)); \
    sceneVar->numEntities = 0; \
    SceneManagerAddScene(sceneManager, sceneVar, startFunc, updateFunc, unloadFunc);    /**< Macro to initialize a scene. */

/**
 * @brief Struct representing a scene.
 * 
 * This struct represents a scene.
 * 
 */
typedef struct _Scene {
    Shader* shader;         /**< Shader of the scene. */
    Shader* textShader;     /**< Text shader of the scene. */
    Skybox* skybox;         /**< Skybox of the scene. */
    Camera* camera;         /**< Camera of the scene. */
    Entity entities[MAX_ENTITIES];      /**< Array of entities. */
    int numEntities;        /**< Number of entities. */
    float deltaTime;        /**< Delta time of the scene. */
    void (*start)(struct _Scene* scene, GameState* gameState);      /**< Start function of the scene. */
    void (*update)(struct _Scene* scene, GameState* gameState);     /**< Update function of the scene. */
    void (*unload)(struct _Scene* scene);                    /**< Unload function of the scene. */
} Scene;

/**
 * @brief Function to create an entity.
 * 
 * This function creates an entity.
 * 
 * @param scene Pointer to the scene.
 * @return Pointer to the entity.
 */
Entity* createEntity(Scene* scene);

/**
 * @brief Function to free a scene.
 * 
 * This function frees a scene.
 * 
 * @param scene Pointer to the scene.
 */
void freeScene(Scene* scene);

/**
 * @brief Function to free an entity.
 * 
 * This function frees an entity.
 * 
 * @param e Pointer to the entity.
 */
void* freeEntity(Entity* e); 