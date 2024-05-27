#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Enemy.h"
#include <Renderer.h>
#include <Inventory.h>

#define NBPARTMAP 9

void startMainScene(Scene* scene, GameState* gameState);
void updateMainScene(Scene* scene, GameState* gameState);
void unloadMainScene(Scene* scene);