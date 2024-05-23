#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include <Dungeon.h>
#include <Ennemy.h>
void DungeonMainScene(Scene* scene, GameState* gameState);
void updateDungeonScene(Scene* scene, GameState* gameState);
void unloadDungeonScene(Scene* scene);