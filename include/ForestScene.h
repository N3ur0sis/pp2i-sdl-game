#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include <Ennemy.h>
#define FLAMEDIST 2.0f

void ForestMainScene(Scene* scene, GameState* gameState);
void updateForestScene(Scene* scene, GameState* gameState);
void unloadForestScene(Scene* scene);