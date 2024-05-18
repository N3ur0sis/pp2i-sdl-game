#include <Engine.h>
#include <Textures.h>
#include <Controls.h>
#include <SceneManager.h>
#include <System.h>
#include <StartScene.h>


/* Entry point of the program */
int main(void){

    SceneManager sceneManager;
    SceneManagerInit(&sceneManager);

    /* Create an instance of the application */
    Application* game = ApplicationCreate(sceneManager.gameState.g_WindowWidth,sceneManager.gameState.g_WindowHeight,sceneManager.gameState.g_WindowTitle);


    Scene mainScene;
    mainScene.numEntities = 0;
    SceneManagerAddScene(&sceneManager, &mainScene, startMainScene, updateMainScene);

    SceneManagerSetCurrentScene(&sceneManager, 0);

    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    while (game->running) {
        StartFrame(game);
        Uint32 currentTime = SDL_GetTicks();
        mainScene.deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        physicsSystem(&mainScene);

        SceneManagerUpdateCurrentScene(&sceneManager);
        cameraControl(&mainScene.camera);

        renderSystem(&mainScene);

        EndFrame(game);
    }

    /* Clean every resource allocated */
    ModelFree((Model*)getComponent(&mainScene.entities[1], COMPONENT_RENDERABLE));
    ModelFree((Model*)getComponent(&mainScene.entities[3], COMPONENT_RENDERABLE));
    free(mainScene.camera);
    DeleteShaders(mainScene.shader);
    SkyboxDelete(mainScene.skybox);
    WindowDelete(game->window);
    EngineQuit();
}
