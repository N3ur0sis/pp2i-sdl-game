#include <Event.h>

void HandleChangeScene(SceneManager* sceneManager){
            /* Free current Scene */
            SceneManagerUnloadCurrentScene(sceneManager, sceneManager->currentSceneIndex);
            
            /* Set new scene */
            sceneManager->currentSceneIndex = sceneManager->gameState.nextSceneIndex;
            SceneManagerSetCurrentScene(sceneManager, sceneManager->currentSceneIndex);
            sceneManager->gameState.change = false;
            sceneManager->gameState.nextSceneIndex = -1;
}

void ChangeSceneEvent(int nextSceneIndex){
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = CHANGE_SCENE_EVENT;
    int* index = (int*)event.user.data1;
    index = nextSceneIndex;
    SDL_PushEvent(&event);
}