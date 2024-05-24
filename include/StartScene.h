#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Enemy.h"
#include <Renderer.h>
#include <Inventory.h>
#include <Marchand.h>

void startStartScene(Scene* scene, GameState* gameState);
void updateStartScene(Scene* scene, GameState* gameState);
void unloadStartScene(Scene* scene);