#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Ennemy.h"
#include <Renderer.h>


Entity* createMarchand(Scene* scene, vec3 position, vec3 scale, vec3 rotation);
void talkToMarchandStart(float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy);
void talkToMarchandMain(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy);
void tradingWithMarchand(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader,int* click_counter, bool* is_clicking, bool* isBusy);