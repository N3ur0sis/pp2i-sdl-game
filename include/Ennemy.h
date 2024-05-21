#pragma once
#include <Model.h>
#include <Animator.h>
#include <Entity.h>
#include <Scene.h>
Entity* create_golem(Scene* scene);
Entity* golemLogic(Scene* scene,GameState* gameState,Entity* golem,Entity* player);
