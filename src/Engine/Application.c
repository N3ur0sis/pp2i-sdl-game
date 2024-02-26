#include "Window.h"
#include "Engine.h"
#include "Shader.h"
#include "Mesh.h"
#include "ModelLoader.h"
#include <stdbool.h>


#define WIDTH 800
#define HEIGHT 600


int main(){

    SDL_Window* window = window_create(WIDTH, HEIGHT, "Game");
    initOpenGL();
    GLuint shaderProgram = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(shaderProgram);
    /*******************TEMPORARY***********************/
    /***************************************************/

    Vector* vertices1 = createVector(VECTOR);
    Vector* normals1 = createVector(VECTOR);
    Vector* uvs1 = createVector(VECTOR);
    Vector* indices1 = createVector(VECTOR);
    ModelLoader("../ressources/teapot.obj", &vertices1, &normals1, &uvs1, &indices1);

    Mesh* rectangle = mesh_create(toVertices(vertices1), toIndices(indices1), vertices1->size, numElements(indices1));

    SDL_Event event;

    bool done = false;
    //Game Loop
    while(!done) {
        
        //Input Handling
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                done = true;
            }
        }

        //Game Logic
        //...

        //Rendering
        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glClearColor(.08f,.08f,.08f,0);
        mesh_draw(rectangle);
        glBindVertexArray(0);
        SDL_GL_SwapWindow(window);
    }
    //CleanUp
    SDL_DestroyWindow(window);
    SDL_Quit();
}
