#include <SceneManager.h>


SceneManager* SceneManagerInit() {
    SceneManager* manager = (SceneManager*)calloc(1,sizeof(SceneManager));

    manager->currentSceneIndex = -1;
    manager->numScenes = 0;

    /* TODO: Load GameState from Save File*/
    manager->gameState.enemyIsAttacking = false;
    manager->gameState.playerIsAttacking = false; 
    manager->gameState.playerHealth = 100.0f;
    manager->gameState.inventory = InventoryCreate(500);
    manager->gameState.marchantInventory = InventoryCreate(500);
    manager->gameState.g_WindowWidth = 1280;
    manager->gameState.g_WindowHeight = 720;
    manager->gameState.isPlayerDead = false;
    manager->gameState.change = false;
    manager->gameState.nextSceneIndex = -1;
    manager->gameState.isForestDungeonDone = false;
    manager->gameState.pauseMenu = NULL;
    manager->gameState.restarting = false;
    manager->gameState.money = 1000;
    
    return manager;
}
void SceneManagerAddScene(SceneManager* manager, Scene* scene, void (*start)(Scene*,GameState*), void (*update)(Scene*, GameState*),void (*unload)(Scene*)) {
    if (manager->numScenes < MAX_SCENES) {
        scene->start = start;
        scene->update = update;
        scene->unload = unload;
        manager->scenes[manager->numScenes++] = scene;
    }
}

void SceneManagerSetCurrentScene(SceneManager* manager, int index) {
    if (index >= 0 && index < manager->numScenes) {
        manager->currentSceneIndex = index;
        manager->scenes[index]->start(manager->scenes[index], &manager->gameState);
    }
}

void SceneManagerUpdateCurrentScene(SceneManager* manager) {
    if (manager->currentSceneIndex >= 0 && manager->currentSceneIndex < manager->numScenes) {
        manager->scenes[manager->currentSceneIndex]->update(manager->scenes[manager->currentSceneIndex], &manager->gameState);
    }
}
void freeSceneManager(SceneManager* manager) {
    if (manager == NULL) return;

    // Free all scenes
    for (int i = 0; i < manager->numScenes; i++) {
        if (manager->scenes[i] != NULL) {
            freeScene(manager->scenes[i]);
        }
    }    

}

void SceneManagerUnloadCurrentScene(SceneManager* manager, int index) {
        manager->scenes[manager->currentSceneIndex]->unload(manager->scenes[manager->currentSceneIndex]);
}

