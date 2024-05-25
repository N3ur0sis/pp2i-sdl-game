#pragma once 
#include <Scene.h>

#define MAX_SCENES 10

typedef struct SceneManager {
    Scene* scenes[MAX_SCENES];
    int currentSceneIndex;
    int numScenes;
    GameState gameState;
    
} SceneManager;

SceneManager* SceneManagerInit();
void SceneManagerAddScene(SceneManager* manager, Scene* scene, void (*start)(Scene*,GameState*), void (*update)(Scene*,GameState*),void (*unloadStartScene)(Scene*));
void SceneManagerSetCurrentScene(SceneManager* manager, int index);
void SceneManagerUpdateCurrentScene(SceneManager* manager);
void freeSceneManager(SceneManager* manager);
void SceneManagerUnloadCurrentScene(SceneManager* manager, int index);

