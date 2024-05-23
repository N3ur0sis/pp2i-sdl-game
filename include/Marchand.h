#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Ennemy.h"
#include <Renderer.h>


Entity* createMarchand(Scene* scene, vec3 position, vec3 scale, vec3 rotation);
void talkToMarchand(GameState* gameState, Scene* scene, int* click_counter, bool* is_clicking, bool* isBusy);
