#pragma once 
#include "Scene.h"
#include <GameState.h>

#define MAX_SCENES 10

typedef struct SceneManager {
    Scene* scenes[MAX_SCENES];
    int currentSceneIndex;
    int numScenes;
    GameState gameState;
    
} SceneManager;

void SceneManagerInit(SceneManager* manager);
void SceneManagerAddScene(SceneManager* manager, Scene* scene, void (*start)(Scene*), void (*update)(Scene*));
void SceneManagerSetCurrentScene(SceneManager* manager, int index);
void SceneManagerUpdateCurrentScene(SceneManager* manager);
void freeSceneManager(SceneManager* manager);