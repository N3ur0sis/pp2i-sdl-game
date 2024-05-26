/**
 * @file Renderer.h
 * @brief Header file for the renderer component.
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/cglm.h> 

/**
 * @brief Function to render text.
 * 
 * This function renders text.
 * 
 * @param message Message to render.
 * @param color Color of the text.
 * @param x X position of the text.
 * @param y Y position of the text.
 * @param size Size of the text.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 * @param shaderProgram Shader program.
 */
void RenderText(const char* message, SDL_Color color, int x, int y, int size, int windowWidth, int windowHeight, GLuint shaderProgram);

/**
 * @brief Function to render an image.
 * 
 * This function renders an image.
 * 
 * @param path Path to the image.
 * @param x X position of the image.
 * @param y Y position of the image.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 * @param shaderProgram Shader program.
 */
void RenderImage(const char* path, int x, int y, int windowWidth, int windowHeight, GLuint shaderProgram);

/**
 * @brief Function to render a square.
 * 
 * This function renders a square.
 * 
 * @param x X position of the square.
 * @param y Y position of the square.
 * @param size Size of the square.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 * @param shaderProgram Shader program.
 */
void RenderSquare(int x, int y, int size, int windowWidth, int windowHeight, GLuint shaderProgram);