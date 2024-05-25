#pragma once

#include <Model.h>
#include <Animator.h>
#include <Entity.h>
#include <Scene.h>

Entity *create_golem(Scene* scene,float x,float y,float z,float scale);
Entity* create_golemBlue(Scene* scene,float x,float y,float z,float scale);
Entity* create_golemPurple(Scene* scene,float x,float y,float z,float scale);
void golemLogic(Scene* scene,GameState* gameState,Entity* golem,Entity* player);

Entity* create_gobelin(Scene* scene,float x,float y,float z,float scale);
Entity* create_skeleton(Scene* scene,float x,float y,float z,float scale);