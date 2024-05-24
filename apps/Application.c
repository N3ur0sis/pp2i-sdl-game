#include <Engine.h>
#include <System.h>

/* Game-Related Includes*/
#include <Player.h>
#include <StartScene.h>
#include <MainScene.h>
#include <ForestScene.h>
#include <DungeonScene.h>


/* Entry point of the program */
int main(void){

    /* Initialize the Engine */
    Application* game = ApplicationCreate(1280,720,"GAME");

    /*Initialize the Scene Manager*/
    SceneManager* sceneManager = SceneManagerInit();

    /* Initialize the Audio System */
    TempAudioImpl();
    
    /* Initializations of Scenes */
    INIT_SCENE(startScene, sceneManager, startStartScene, updateStartScene, unloadStartScene);
    INIT_SCENE(dungeonScene, sceneManager, DungeonMainScene, updateDungeonScene, unloadDungeonScene);
    INIT_SCENE(forestScene, sceneManager, ForestMainScene, updateForestScene, unloadStartScene);
    INIT_SCENE(mainScene, sceneManager, startMainScene, updateMainScene, unloadStartScene);

    /* Set Default Current Scene */
    SceneManagerSetCurrentScene(sceneManager, sceneManager->gameState.currentSceneIndex);

    Uint32 last = SDL_GetTicks();
    int nbframe;
    /* Game Loop */
    while (game->running) {
        Uint64 current = SDL_GetTicks();
        nbframe++;
        if(current - last >= 1000.0f){
            printf("FPS: %d\n", nbframe);
            nbframe = 0;
            last += 1000.0f;
        }
        /* Update Frame */
        StartFrame(game,&sceneManager->gameState, sceneManager);
        

        physicsSystem(sceneManager->scenes[sceneManager->currentSceneIndex]);
        renderSystem(sceneManager->scenes[sceneManager->currentSceneIndex],&sceneManager->gameState);
        SceneManagerUpdateCurrentScene(sceneManager);
        cameraControl(sceneManager->scenes[sceneManager->currentSceneIndex]->camera);
        EndFrame(game);

        }
    freeInventory(sceneManager->gameState.inventory);
    freeInventory(sceneManager->gameState.marchantInventory);

    /* Clean every resource allocated */
    //freeScene(mainScene);
    //freeSceneManager(&sceneManager);
    WindowDelete(game->window);
    EngineQuit();
}