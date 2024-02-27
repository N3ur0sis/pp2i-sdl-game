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

//GLOBAL VARIABLES
#define WIDTH 800
#define HEIGHT 600


int main(void){

    //Initialize SDL and Create window
    SDL_Window* window = window_create(WIDTH, HEIGHT, "Game");
    //Initialize OpenGL and create ViewPort
    initOpenGL(WIDTH, HEIGHT);
    //Load and Compile Shaders into OpenGL
    Shader* shader = LoadShaders("vertex.glsl", "fragment.glsl");
    useShaders(shader->program);
    //Create and Initialize scene Camera
    Camera* camera = camera_create(0.0f, 1.0f, 5.0f, WIDTH, HEIGHT);
    Time* time = (Time*)malloc(sizeof(Time));
    /*******************DEMONSTRATION***********************/
    GLfloat vertices[] = {
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f
    };
    GLuint indices[] = {0, 2, 3, 0, 3, 1,
                          2, 6, 7, 2, 7, 3,
                          6, 4, 5, 6, 5, 7,
                          4, 0, 1, 4, 1, 5,
                          1, 3, 7, 1, 7, 5,
                          4, 6, 2, 4, 2, 0};

    Vector* vertices1 = createVector(VECTOR);
    Vector* normals1 = createVector(VECTOR);
    Vector* uvs1 = createVector(VECTOR);
    Vector* indices1 = createVector(VECTOR);
    ModelLoader("../ressources/teapot.obj", &vertices1, &normals1, &uvs1, &indices1);

    //Create and initialize a cube
    Mesh* rectangle = mesh_create(vertices, indices, 24, 36);
    Mesh* teapot = mesh_create(toVertices(vertices1), toIndices(indices1), vertices1->size, numElements(indices1));
    /***************************************************/

    SDL_Event e;
    //Game Loop
    bool done = false;
    time->lastUpdate = SDL_GetTicks();
    while(!done) {

        //Per-frame time logic
        time->currentUpdate = SDL_GetTicks();
        time->deltaTime = (time->currentUpdate - time->lastUpdate) / 1000.0f;

        //Input Handling
        while(SDL_PollEvent(&e)){
        processInput(&e, &done, camera, time);
        }
        //Game Logic
        //...

        //Rendering
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        mesh_draw(teapot, shader, camera, time);
        glBindVertexArray(0);
        SDL_GL_SwapWindow(window);
    }

    //CleanUp
    free(teapot);
    free(rectangle);
    free(camera);
    free(shader);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
