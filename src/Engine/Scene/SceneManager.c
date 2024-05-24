#include <SceneManager.h>

void SceneManagerInit(SceneManager* manager) {
    manager->currentSceneIndex = -1;
    manager->numScenes = 0;

        // Initialize the game state
    manager->gameState.enemyIsAttacking = false;
    manager->gameState.playerIsAttacking = false; 
    manager->gameState.playerHealth = 100.0f;
    manager->gameState.inventory = InventoryCreate(500);
    manager->gameState.marchantInventory = InventoryCreate(500);
    manager->gameState.g_WindowWidth = 1280;
    manager->gameState.g_WindowHeight = 720;
    manager->gameState.g_WindowTitle = "Game";
     manager->gameState.isPlayerDead = false;
    manager->gameState.change = false;
    manager->gameState.nextSceneIndex = -1;
    manager->gameState.isForestDungeonDone = false;
}
void SceneManagerAddScene(SceneManager* manager, Scene* scene, void (*start)(Scene*), void (*update)(Scene*),void (*unload)(Scene*)) {
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