#include <Engine.h>
#include <Textures.h>
#include <Controls.h>
#include <SceneManager.h>
#include <System.h>
#include <StartScene.h>
#include <MainScene.h>
#include <DungeonScene.h>
#include <SDL2/SDL_mixer.h>
#include <ForestScene.h>
#include <Renderer.h>

/* Entry point of the program */
int main(void){

    /*Create the Scene Manager*/
    SceneManager sceneManager;
    SceneManagerInit(&sceneManager);

    /* Create an instance of the application */
    Application* game = ApplicationCreate(sceneManager.gameState.g_WindowWidth,sceneManager.gameState.g_WindowHeight,sceneManager.gameState.g_WindowTitle);

    /* Music Player*/
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    Mix_Music *bgm = Mix_LoadMUS("assets/music/my-little-garden-of-eden-112845.mp3");
    if (bgm == NULL) {
    fprintf(stderr, "Failed to load background music: %s\n", Mix_GetError());
    return -1;
    }

    if (Mix_PlayMusic(bgm, -1) == -1) {  
    fprintf(stderr, "SDL_mixer could not play music! SDL_mixer Error: %s\n", Mix_GetError());
    return -1;
    }
    Mix_VolumeMusic(0); // 64=50% du volume
    
    /* Init of Start Scene*/
    Scene* startScene = (Scene*)calloc(1,sizeof(Scene));
    startScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, startScene, startStartScene, updateStartScene,unloadStartScene);
    
    
    /* Init of Dungeon Scene*/
    Scene* dungeonScene = (Scene*)calloc(1,sizeof(Scene));
    dungeonScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, dungeonScene, DungeonMainScene, updateDungeonScene,unloadDungeonScene);
    
     /* Init of Forest Scene*/

    Scene* forestScene = (Scene*)calloc(1,sizeof(Scene));
    forestScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, forestScene, ForestMainScene, updateForestScene,unloadStartScene);


    Scene* mainScene = (Scene*)calloc(1,sizeof(Scene));
    mainScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, mainScene, startMainScene, updateMainScene,unloadStartScene);

    int current_scene = 0;
    SceneManagerSetCurrentScene(&sceneManager, current_scene);

    TTF_Init();

    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    while (game->running) {
        /*Changement de scene*/
        if (sceneManager.gameState.change){
            //Unload current scene
            SceneManagerUnloadCurrentScene(&sceneManager, sceneManager.currentSceneIndex);
            //Load the next one
            sceneManager.currentSceneIndex = sceneManager.gameState.nextSceneIndex;
            SceneManagerSetCurrentScene(&sceneManager, sceneManager.currentSceneIndex);
            sceneManager.gameState.change = false;
            sceneManager.gameState.nextSceneIndex = -1;
        }
        else {
            Uint32 currentTime = SDL_GetTicks();
            StartFrame(game,&sceneManager.gameState);
            
            sceneManager.scenes[sceneManager.currentSceneIndex]->deltaTime = (currentTime - lastTime) / 1000.0f;
            physicsSystem(sceneManager.scenes[sceneManager.currentSceneIndex]);
            renderSystem(sceneManager.scenes[sceneManager.currentSceneIndex],&sceneManager.gameState);
            SceneManagerUpdateCurrentScene(&sceneManager);
            cameraControl(sceneManager.scenes[sceneManager.currentSceneIndex]->camera,&sceneManager.gameState);
            lastTime = currentTime;
            EndFrame(game);
        }
    }

    /* Clean every resource allocated */
    //freeScene(mainScene);
    //freeSceneManager(&sceneManager);
    Mix_FreeMusic(bgm);
    WindowDelete(game->window);
    EngineQuit();
}