#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <Window.h>
#include <Controls.h>
#include <Shader.h>
#include <objLoader.h>
#include <Mesh.h>
#include <Textures.h>
#include <Time.h>
#include <Light.h>
#include <stdbool.h>
#include <math.h>
#include <cglm/cglm.h>
#include <cglm/call.h>



void engine_start(float width, float height);
void engine_quit();

