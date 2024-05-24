/**
 * @file Time.h
 * @brief Time management structures and definitions for the application.
 * @author Aymeric ROBERT
 */

#pragma once

#include <SDL2/SDL.h>

/**
 * @brief Structure for managing time-related information in the application.
 */
typedef struct {
    Uint32 lastUpdate;      /**< The timestamp of the last update in milliseconds. */
    Uint32 currentUpdate;   /**< The timestamp of the current update in milliseconds. */
    float deltaTime;        /**< The time difference between the last and current update in seconds. */
    unsigned int nbFrames;  /**< The number of frames since the last second. */
} Time;
