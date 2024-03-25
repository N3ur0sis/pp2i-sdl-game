#include <Window.h>
#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Light.h>
#include <objLoader.h>
#include <Textures.h>
#include <Scene.h>

//GLOBAL VARIABLES
static const int g_WindowWidth = 1280;
static const int g_WindowHeight = 720;
static const char* g_WindowTitle = "Game";

//Entry Point of the Game
int main(void){

    //Initialize SDL and Create window
    Window* window = WindowInit(g_WindowWidth, g_WindowHeight, g_WindowTitle);
    if(window == NULL){
        return 1;
    }
    
    //Initialize OpenGL
    GL_Init();

    //Load and Compile Shaders into OpenGL
    Shader* shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    UseShaders(shader);

    //Create and Initialize scene Camera
    Camera* camera = camera_create(0.0f, 8.0f, 5.0f, g_WindowWidth, g_WindowHeight);

    //Initialize Engine Components
    Time* time = (Time*)malloc(sizeof(Time));
    SDL_Event e;


    /***************DEMONSTRATION SCENE*****************/
    Model* model = ModelCreate("assets/models/vampire/dancing_vampire.dae");
    
    
	vec3 color = {1.0f, 0.8f, 1.0f};
	light_setAmbientLight(shader, color, 0.3f);
    vec3 pointColor = {1.0f, 0.7f, 1.0f};
    vec3 pointPosition = {10.0f, 5.0f, 2.0f};
	pointLight *point = light_createPointLight(shader, pointColor, pointPosition, 5.0f, 0.6f);
    /***************************************************/



    //Game Loop
    bool done = false;
    time->lastUpdate = SDL_GetTicks();
    int nbFrames = 0;
    while(!done) {

        //Per-frame time logic
        time->currentUpdate = SDL_GetTicks();
        nbFrames++;
        if( time->currentUpdate - time->lastUpdate >= 1000.0f){
            printf("%d fps\n", nbFrames);
            nbFrames = 0;
            time->lastUpdate += 1000.0f;
        }
        time->deltaTime = (time->currentUpdate - time->lastUpdate) / 1000.0f;

        //Input Handling
        while(SDL_PollEvent(&e)){
            processInput(&e, &done);
        }
        
        //Rendering
        light_updatePointLight(shader, point);
        cameraControl(camera);
        // Clear the render output and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ModelDraw(model, shader, camera);
        SDL_GL_SwapWindow(window->m_window);
    }

    //CleanUp
    free(camera);
    DeleteShaders(shader);
    WindowDestroy(window);
    GL_Quit();
}
