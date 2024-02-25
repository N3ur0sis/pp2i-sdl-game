#include "Window.h"
#include "Engine.h"
#include "Shader.h"
#include "Mesh.h"
#include <math.h>
#include <stdbool.h>
#include <cglm/cglm.h>   /* for inline */
#include <cglm/call.h>   /* for library call (this also includes cglm.h) */


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
    /***************************************************/

    Mesh* rectangle = mesh_create(vertices, indices, 24, 36);

    SDL_Event event;

    //Game Loop    
    bool done = false;
    Uint32 lastUpdate = SDL_GetTicks();
    while(!done) {
        Uint32 current = SDL_GetTicks();
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
        float dT = (current - lastUpdate) / 1000.0f;
        mat4 model;
        glm_mat4_identity(model);
        vec3 rotAxis = {0.5f, 1.0f, 0.0f};
        glm_rotate(model, glm_rad(50.0f)*dT, rotAxis);
        mat4 view;
        glm_mat4_identity(view);
        vec3 transAxis = {0.0f, 0.0f, -3.0f};
        glm_translate(view, transAxis);
        mat4 projection;
        glm_perspective(glm_rad(60.0f), (float)(WIDTH)/(float)HEIGHT, 0.1f, 100.0f, projection);

        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);
        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)view);
        int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float*)projection);

        glClearColor(.08f,.08f,.08f,0);
        mesh_draw(rectangle);
        glBindVertexArray(0);
        SDL_GL_SwapWindow(window);
    }
    //CleanUp
    SDL_DestroyWindow(window);
    SDL_Quit();
}
