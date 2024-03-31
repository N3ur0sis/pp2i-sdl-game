#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>
#include <Textures.h>
#include <Skybox.h>


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

    /* Start Function, create objects in scene */
    Model* player = (Model*)calloc(1, sizeof(Model));
    ModelCreate(player, "assets/models/LoPotitChat/LoPotitChat.obj");
    player->position[1] += 2.0f;
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->scale);
    Model* map = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/map/map.obj");
	light_setAmbientLight(shader, (vec3){0.8f, 0.8f, 1.0f}, 0.6f);
	pointLight *point = light_createPointLight(shader, (vec3){0.9f, 0.9f, 1.0f}, (vec3){20.0f, 30.0f, -20.0f}, 10.0f, 0.6f);
    
    /* Create a scene camera */
    Camera* camera = camera_create(player->position[0], player->position[1]+17.5f, player->position[2]-17.5f, g_WindowWidth, g_WindowHeight);

    /* Create a skybox */
    Skybox* skybox = SkyboxCreate();

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    /* Game Loop */
    while(game->running) {
        StartFrame(game);


        
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        treatMovingInput(player->position, player->rotation, deltaTime, camera);



        /* Rendering Scene */
        UseShaders(shader);
        ModelDraw(player, shader, camera);
        ModelDraw(map, shader, camera);
        glBindVertexArray(0);
        cameraControl(camera);
        light_updatePointLight(shader, point);

        /* Rendering SkyBox */
        SkyboxDraw(skybox,camera);


        EndFrame(game);
    }

    /* Clean every ressources allocated */
    ModelFree(player);
    ModelFree(map);
    free(camera);
    DeleteShaders(shader);
    SkyboxDelete(skybox);
    WindowDelete(game->window);
    EngineQuit();
}
