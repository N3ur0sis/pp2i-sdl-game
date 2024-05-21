#include <Engine.h>
#include <Textures.h>
#include <Controls.h>
#include <SceneManager.h>
#include <System.h>
#include <StartScene.h>
#include <DungeonScene.h>
#include <SDL_mixer.h>
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
    Mix_VolumeMusic(10); // 64=50% du volume
    
    /* Init of Start Scene*/
    Scene* mainScene = (Scene*)calloc(1,sizeof(Scene));
    mainScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, mainScene, startMainScene, updateMainScene,unloadStartScene);
    
    
    /* Init of Dungeon Scene*/
    Scene* dungeonScene = (Scene*)calloc(1,sizeof(Scene));
    dungeonScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, dungeonScene, DungeonMainScene, updateDungeonScene,unloadDungeonScene);
    
     /* Init of Dungeon Scene*/
    Scene* forestScene = (Scene*)calloc(1,sizeof(Scene));
    forestScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, forestScene, ForestMainScene, updateForestScene,unloadStartScene);

    int current_scene = 1;
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
            printf(" next scene = %d\n", sceneManager.currentSceneIndex);
            SceneManagerSetCurrentScene(&sceneManager, sceneManager.currentSceneIndex);
            printf("on a fini de charger\n");
            sceneManager.gameState.change = false;
            sceneManager.gameState.nextSceneIndex = -1;
        }
        else {
            Uint32 currentTime = SDL_GetTicks();
            StartFrame(game);
            
            sceneManager.scenes[sceneManager.currentSceneIndex]->deltaTime = (currentTime - lastTime) / 1000.0f;
            physicsSystem(sceneManager.scenes[sceneManager.currentSceneIndex]);
            SceneManagerUpdateCurrentScene(&sceneManager);
            cameraControl(sceneManager.scenes[sceneManager.currentSceneIndex]->camera);
            renderSystem(sceneManager.scenes[sceneManager.currentSceneIndex]);
            lastTime = currentTime;
            EndFrame(game);
        }
        
        

    }

    /* Clean every resource allocated */
    freeScene(mainScene);
    //freeSceneManager(&sceneManager);
    Mix_FreeMusic(bgm);
    WindowDelete(game->window);
    EngineQuit();
}