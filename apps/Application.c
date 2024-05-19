#include <Engine.h>
#include <Textures.h>
#include <Controls.h>
#include <SceneManager.h>
#include <System.h>
#include <StartScene.h>
#include <DungeonScene.h>
#include <SDL_mixer.h>
#include "SDL2/SDL.h"
#include <Renderer.h>


/* Entry point of the program */
int main(void){

    SceneManager sceneManager;
    SceneManagerInit(&sceneManager);

            SDL_Color color = {255, 0, 0, 0}; // Red

    /* Create an instance of the application */
    Application* game = ApplicationCreate(sceneManager.gameState.g_WindowWidth,sceneManager.gameState.g_WindowHeight,sceneManager.gameState.g_WindowTitle);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

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
    SceneManagerAddScene(&sceneManager, mainScene, startMainScene, updateMainScene);
    
    /* Init of Dungeon Scene*/
    Scene* dungeonScene = (Scene*)calloc(1,sizeof(Scene));
    dungeonScene->numEntities = 0;
    SceneManagerAddScene(&sceneManager, dungeonScene, DungeonMainScene, updateDungeonScene);
    
    int current_scene = 1;
    SceneManagerSetCurrentScene(&sceneManager, current_scene);


    SceneManagerSetCurrentScene(&sceneManager, 0);


    Shader* textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");

    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }


    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    while (game->running) {
        Uint32 currentTime = SDL_GetTicks();


        /* Example of rendering text and Image*/
        RenderText("Press E to pick up", (SDL_Color){255, 255, 255, 0}, 640, 360, 12, 1280, 720, textShader->m_program);
        for (int i = 0; i < 10; i++)
        {
            
            RenderImage("assets/images/heart.png", (SDL_Color){255, 255, 255, 0}, 1280 - i*20, 10, 20, 1280, 720, textShader->m_program);
        }
        

     

        switch (current_scene)
        {
        case 0:
            StartFrame(game);
            mainScene->deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;
            physicsSystem(mainScene);
            SceneManagerUpdateCurrentScene(&sceneManager);
            cameraControl(mainScene->camera);
            renderSystem(mainScene);
            EndFrame(game);
            break;
        case 1:
            StartFrame(game);
            dungeonScene->deltaTime = (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;
            physicsSystem(dungeonScene);
            SceneManagerUpdateCurrentScene(&sceneManager);
            cameraControl(dungeonScene->camera);
            renderSystem(dungeonScene);
            EndFrame(game);
        default:
            break;
        }
        
    }

    /* Clean every resource allocated */
    ModelFree((Model*)getComponent(&mainScene->entities[1], COMPONENT_RENDERABLE));
    ModelFree((Model*)getComponent(&mainScene->entities[3], COMPONENT_RENDERABLE));
    free(mainScene->camera);
    DeleteShaders(mainScene->shader);
    SkyboxDelete(mainScene->skybox);
    WindowDelete(game->window);
    EngineQuit();
}
