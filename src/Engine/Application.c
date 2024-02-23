#include "Window.h"
#include "Engine.h"
#include "Shader.h"
#include "Mesh.h"
#include <stdbool.h>


#define WIDTH 800
#define HEIGHT 600


int main(){

    SDL_Window* window = window_create(WIDTH, HEIGHT, "Game");
    initOpenGL();
    GLuint shaderProgram = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(shaderProgram);
    /*******************TEMPORARY***********************/
    GLfloat vertices[] = {
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };
    GLuint indices[] = {0, 2, 3, 0, 3, 1};
    /***************************************************/

    Mesh* rectangle = mesh_create(vertices, indices, 4, 6);

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
