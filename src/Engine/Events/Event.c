/**
 * @file Event.c
 * @brief Implementation of scene management event functions for the application.
 * @author Aymeric ROBERT
 */

#include <Event.h>
#include <stdio.h>

/**
 * @brief Logs an SDL error message.
 * 
 * @param msg The error message to log.
 */
static void logSDLError(const char* msg) {
    fprintf(stderr, "ERROR: %s: %s\n", msg, SDL_GetError());
}

/**
 * @brief Handles changing the current scene in the scene manager.
 * 
 * This function processes the scene change event and updates the scene manager accordingly.
 * It unloads the current scene and sets the new scene based on the next scene index stored in the game state.
 * 
 * @param sceneManager Pointer to the SceneManager instance.
 */
void HandleChangeScene(SceneManager* sceneManager) {
    if (!sceneManager) {
        logSDLError("SceneManager is NULL in HandleChangeScene");
        return;
    }

    /* Unload the current scene */
    SceneManagerUnloadCurrentScene(sceneManager, sceneManager->currentSceneIndex);

    /* Set the new scene */
    sceneManager->currentSceneIndex = sceneManager->gameState.nextSceneIndex;
    SceneManagerSetCurrentScene(sceneManager, sceneManager->currentSceneIndex);

    /* Reset the game state change flag and next scene index */
    sceneManager->gameState.change = false;
    sceneManager->gameState.nextSceneIndex = -1;
}

/**
 * @brief Creates and pushes a scene change event.
 * 
 * This function creates a custom SDL event for changing scenes and pushes it to the SDL event queue.
 * It allocates memory for the next scene index and assigns it to the event's user data.
 * 
 * @param nextSceneIndex The index of the next scene to switch to.
 */
void ChangeSceneEvent(int nextSceneIndex) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = CHANGE_SCENE_EVENT;

    /* Allocate memory for the next scene index and assign it to the event */
    int* pNextSceneIndex = malloc(sizeof(int));
    if (!pNextSceneIndex) {
        fprintf(stderr, "ERROR: Failed to allocate memory for scene index\n");
        return;
    }
    *pNextSceneIndex = nextSceneIndex;
    event.user.data1 = pNextSceneIndex;

    if (SDL_PushEvent(&event) != 1) {
        logSDLError("Failed to push change scene event");
        free(pNextSceneIndex);
    }
}
