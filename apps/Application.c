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

    /* Start Function, create objects in scene */
    Model* model = (Model*)calloc(1, sizeof(Model));
    ModelCreate(model, "assets/models/LoPotitChat/LoPotitChat.obj");
    Model* map = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/map/map.obj");

    printf("Model coordinates: %f %f %f\n", model->position[0], model->position[1], model->position[2]);
    printf("Model orientation: %f %f %f\n", model->rotation[0], model->rotation[1], model->rotation[2]);

    
	light_setAmbientLight(shader, (vec3){1.0f, 0.8f, 1.0f}, 0.3f);
	pointLight *point = light_createPointLight(shader, (vec3){1.0f, 0.7f, 1.0f}, (vec3){10.0f, 5.0f, 2.0f}, 5.0f, 0.6f);
    model->position[1] = 2.0f;
    /* Create a scene camera */
    Camera* camera = camera_create(model->position[0], model->position[1]+7.5f, model->position[2]-7.5f, g_WindowWidth, g_WindowHeight);

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    /* Game Loop */
    while(game->running) {
        StartFrame(game);
        
        /**Rendering**/
        ModelDraw(model, shader, camera);
        ModelDraw(map, shader, camera);
        cameraControl(camera);
        light_updatePointLight(shader, point);
        /*************/
        printf("Model coordinates: %f %f %f, orientation : %f\n", model->position[0], model->position[1], model->position[2], model->rotation[1]);
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        treatMovingInput(model->position, model->rotation, deltaTime, camera);
        EndFrame(game);
    }

    /* Clean every ressources allocated */
    free(camera);
    ModelFree(model);
    ModelFree(map);
    DeleteShaders(shader);
    WindowDelete(game->window);
    EngineQuit();
}
