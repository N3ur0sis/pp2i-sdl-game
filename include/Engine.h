/**
 * @file Engine.h
 * @brief Engine initialization and management functions. Include this file to implement the engine and start coding a Game.
 * A basic application would contains a while loop with StartFrame and EndFrame until running is false.
 * @author Aymeric ROBERT
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <Window.h>
#include <Audio.h>
#include <Textures.h>
#include <Renderer.h>
#include <Controls.h>

/**
 * @brief Represents the main Engine structure.
 */
typedef struct _Application {
    Window* window;    /**< Pointer to the main application window. */
    Time* time;        /**< Pointer to the time management structure. */
    SDL_Event* event;  /**< Pointer to the SDL event structure. */
    bool running;      /**< Boolean flag indicating if the application is running. */
    bool isPaused;     /**< Boolean flag indicating if the application is paused. */
} Application;

/**
 * @brief Creates a new Application instance.
 * 
 * @param width The width of the application window.
 * @param height The height of the application window.
 * @param title The title of the application window.
 * @return Pointer to the created Application instance.
 */
Application* ApplicationCreate(int width, int height, const char* title);

/**
 * @brief Starts a new frame in the application.
 * 
 * This function should be called at the beginning of each frame to process input and update game state.
 * 
 * @param game Pointer to the Application instance.
 * @param gameState Pointer to the current game state.
 * @param sceneManager Pointer to the scene manager, used to change between scenes. Can be NULL
 */
void StartFrame(Application* game, GameState* gameState, SceneManager* sceneManager);

/**
 * @brief Ends the current frame in the application.
 * 
 * This function should be called at the end of each frame to present the frame.
 * 
 * @param game Pointer to the Application instance.
 */
void EndFrame(Application* game);

/**
 * @brief Initializes the game engine.
 * 
 * This function initializes all necessary subsystems of the game engine.
 * 
 * @return true if the engine was initialized successfully, false otherwise.
 */
bool EngineInit(void);

/**
 * @brief Shuts down the game engine.
 * 
 * This function cleans up and shuts down all subsystems of the game engine.
 */
void EngineQuit(void);

