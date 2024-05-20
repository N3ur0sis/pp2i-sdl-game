#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <glad/glad.h>
#include <cglm/cglm.h> 

void RenderText(const char* message, SDL_Color color, int x, int y, int size, int windowWidth, int windowHeight, GLuint shaderProgram);

void RenderImage(const char* path, int x, int y, int windowWidth, int windowHeight, GLuint shaderProgram);