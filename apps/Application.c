#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>

/* Global variable, only for things that won't change during the game */
static const int g_WindowWidth = 1280;
static const int g_WindowHeight = 720;
static const char* g_WindowTitle = "Game";

/* Entry point of the program */
int main(void){

    /* Create a instance of the application */
    Application* game = ApplicationCreate(g_WindowWidth, g_WindowHeight, g_WindowTitle);

    /* Load and compile shaders */
    Shader* shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");

    /* Use current shaders */
    UseShaders(shader);

    /* Create a scene camera */
    Camera* camera = camera_create(0.0f, 8.0f, 5.0f, g_WindowWidth, g_WindowHeight);

    /* Start Function, create objects in scene */
    Model* model = ModelCreate("assets/models/backpack/backpack.obj");
	light_setAmbientLight(shader, (vec3){1.0f, 0.8f, 1.0f}, 0.3f);
	pointLight *point = light_createPointLight(shader, (vec3){1.0f, 0.7f, 1.0f}, (vec3){10.0f, 5.0f, 2.0f}, 5.0f, 0.6f);
    

    /* Game Loop */
    while(game->running) {
        StartFrame(game);

        /**Rendering**/
        ModelDraw(model, shader, camera);
        cameraControl(camera);
        light_updatePointLight(shader, point);
        /*************/

        EndFrame(game);
    }

    /* Clean every ressources allocated */
    free(camera);
    DeleteShaders(shader);
    WindowDelete(game->window);
    EngineQuit();
}
