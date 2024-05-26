#include <Engine.h>
#include <System.h>

/* Game-Related Includes*/
#include <Player.h>
#include <StartScene.h>
#include <MainScene.h>
#include <ForestScene.h>
#include <DungeonScene.h>
#include <Menu.h>

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

    /* Initialize Menu */
    Menu* menu = MenuPauseInit();
    sceneManager->gameState.pauseMenu = menu;

    /* Set Default Current Scene */
    sceneManager->gameState.currentSceneIndex = 0;
    SceneManagerSetCurrentScene(sceneManager, sceneManager->gameState.currentSceneIndex);

    /* Set Default Camera Position */
    sceneManager->scenes[sceneManager->currentSceneIndex]->camera->Yaw = 180.0f;
    SceneManagerUpdateCurrentScene(sceneManager);
    physicsSystem(sceneManager->scenes[sceneManager->currentSceneIndex]);

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
        
        /* Game Logic */
        if (sceneManager->gameState.mainMenuOpen) {
            RenderText("WELCOME TO THE GAME", (SDL_Color){0,0,0,0}, (&sceneManager->gameState)->g_WindowWidth / 2, 9 * (&sceneManager->gameState)->g_WindowHeight / 10, 50, (&sceneManager->gameState)->g_WindowWidth, (&sceneManager->gameState)->g_WindowHeight, sceneManager->scenes[sceneManager->currentSceneIndex]->textShader->m_program);
            RenderText("PRESS ENTER TO START", (SDL_Color){0,0,0,0}, (&sceneManager->gameState)->g_WindowWidth / 2, 5 * (&sceneManager->gameState)->g_WindowHeight / 10, 40, (&sceneManager->gameState)->g_WindowWidth, (&sceneManager->gameState)->g_WindowHeight, sceneManager->scenes[sceneManager->currentSceneIndex]->textShader->m_program);
        } else {
            if (game->isPaused) {
                    RenderText("MENU", (SDL_Color){0,0,0,0}, (&sceneManager->gameState)->g_WindowWidth / 2, 9 * (&sceneManager->gameState)->g_WindowHeight / 10, 50, (&sceneManager->gameState)->g_WindowWidth, (&sceneManager->gameState)->g_WindowHeight, sceneManager->scenes[sceneManager->currentSceneIndex]->textShader->m_program);
                    MenuPauseDraw(game, &sceneManager->gameState, &sceneManager->scenes[sceneManager->currentSceneIndex]->textShader, sceneManager->gameState.pauseMenu);
            }else{
            physicsSystem(sceneManager->scenes[sceneManager->currentSceneIndex]);
            SceneManagerUpdateCurrentScene(sceneManager);
            cameraControl(sceneManager->scenes[sceneManager->currentSceneIndex]->camera);
            }
        }

        /* Render Frame */
        renderSystem(sceneManager->scenes[sceneManager->currentSceneIndex],&sceneManager->gameState);

        EndFrame(game);

    }

    /* Clean every resource allocated */

    WindowDelete(game->window);
    EngineQuit();
}