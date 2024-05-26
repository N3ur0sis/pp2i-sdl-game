/**
 * @file SceneManager.h
 * @brief Header file for the scene manager component.
*/

#pragma once 
#include <Scene.h>

#define MAX_SCENES 10       /**< Maximum number of scenes. */

/**
 * @brief Structure for the scene manager.
*/
typedef struct SceneManager {
    Scene* scenes[MAX_SCENES];                /**< Array of scenes. */
    int currentSceneIndex;              /**< Index of the current scene. */
    int numScenes;                /**< Number of scenes. */
    GameState gameState;        /**< Game state of the scene manager. */
    
} SceneManager;

/**
 * @brief Function to initialize the scene manager.
 * 
 * This function initializes the scene manager.
 * 
 * @return Pointer to the scene manager.
 */
SceneManager* SceneManagerInit();

/**
 * @brief Function to add a scene to the scene manager.
 * 
 * This function adds a scene to the scene manager.
 * 
 * @param manager Pointer to the scene manager.
 * @param scene Pointer to the scene.
 * @param start Start function of the scene.
 * @param update Update function of the scene.
 * @param unloadStartScene Unload function of the scene.
 */
void SceneManagerAddScene(SceneManager* manager, Scene* scene, void (*start)(Scene*,GameState*), void (*update)(Scene*,GameState*),void (*unloadStartScene)(Scene*));

/**
 * @brief Function to set the current scene.
 * 
 * This function sets the current scene.
 * 
 * @param manager Pointer to the scene manager.
 * @param index Index of the scene.
 */
void SceneManagerSetCurrentScene(SceneManager* manager, int index);

/**
 * @brief Function to update the current scene.
 * 
 * This function updates the current scene.
 * 
 * @param manager Pointer to the scene manager.
 */
void SceneManagerUpdateCurrentScene(SceneManager* manager);

/**
 * @brief Function to free the scene manager.
 * 
 * This function frees the scene manager.
 * 
 * @param manager Pointer to the scene manager.
 */
void freeSceneManager(SceneManager* manager);

/**
 * @brief Function to unload the current scene.
 * 
 * This function unloads the current scene.
 * 
 * @param manager Pointer to the scene manager.
 * @param index Index of the scene.
 */
void SceneManagerUnloadCurrentScene(SceneManager* manager, int index);

