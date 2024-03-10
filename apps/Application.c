#include "Window.h"
#include "Engine.h"
#include "Shader.h"
#include "Mesh.h"
#include "ModelLoader.h"
#include <Time.h>
#include <Controls.h>
#include <math.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <cglm/call.h>
#include <objLoader.h>
#include <Textures.h>

//GLOBAL VARIABLES
static const int WIDTH = 1280;
static const int HEIGHT = 720;


//Entryp Point of the Game
int main(void){

    //Initialize SDL and Create window
    SDL_Window* window = window_create(WIDTH, HEIGHT, "Game");
    //Initialize OpenGL and create ViewPort
    initOpenGL(WIDTH, HEIGHT);
    //Load and Compile Shaders into OpenGL
    Shader* shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    useShaders(shader->program);
    //Create and Initialize scene Camera
    Camera* camera = camera_create(0.0f, 1.0f, 5.0f, WIDTH, HEIGHT);
    //Initialize Engine Components
    Time* time = (Time*)malloc(sizeof(Time));
    SDL_Event e;


    /*******************DEMONSTRATION***********************/
    Obj obj = loadObj("assets/models/table.obj");
    Mesh* cube = mesh_create(obj.vertices, obj.uvs, (GLuint*)obj.indices, obj.numVertices, obj.numIndices);
    load_textures(cube,"assets/images/table.png");
    /***************************************************/


    //Game Loop
    bool done = false;
    time->lastUpdate = SDL_GetTicks();
    while(!done) {

        //Per-frame time logic
        time->currentUpdate = SDL_GetTicks();
        time->deltaTime = (time->currentUpdate - time->lastUpdate) / 1000.0f;

        //Input Handling
        while(SDL_PollEvent(&e)){
            processInput(&e, &done);
        }
        //Game Logic
        //...

        //Rendering
        cameraControl(camera);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        mesh_draw(cube, shader, camera, time);
        //mesh_draw(rectangle, shader, camera, time);
        glBindVertexArray(0);
        SDL_GL_SwapWindow(window);
    }

    //CleanUp
    free(cube);
    free(camera);
    free(shader);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
