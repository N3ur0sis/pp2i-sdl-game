/**
 * @file Event.h
 * @brief Scene management event functions and definitions for the application.
 * @author Aymeric ROBERT
 */

#pragma once

#include <SDL2/SDL.h>
#include <SceneManager.h>

/** Custom SDL event type for changing scenes */
#define CHANGE_SCENE_EVENT (SDL_USEREVENT + 1)

/**
 * @brief Handles changing the current scene in the scene manager.
 * 
 * This function processes the scene change event and updates the scene manager accordingly.
 * 
 * @param sceneManager Pointer to the SceneManager instance.
 */
void HandleChangeScene(SceneManager* sceneManager);

/**
 * @brief Creates and pushes a scene change event.
 * 
 * This function creates a custom SDL event for changing scenes and pushes it to the SDL event queue.
 * 
 * @param nextSceneIndex The index of the next scene to switch to.
 */
void ChangeSceneEvent(int nextSceneIndex);