#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "Mesh.h"
#include "Shader.h"

int main(){
    SDL_Window* window;

    int screen_width = 911;
    int screen_height = 669;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed initialization. ");
        return -1;
    } else {
        printf("SDL successfully initialized.");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("SDL2 Window | OpenGL", 
            0, 
            0, 
            screen_width, 
            screen_height, 
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    (void) context;
    context = SDL_GL_CreateContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    //Initialize our mesh
    Mesh *mesh = malloc(sizeof(Mesh));

    glGenVertexArrays(1, &mesh->VertexArrayID);
    glBindVertexArray(mesh->VertexArrayID);

    GLfloat vertices[] = {
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    GLint triangles[] = {0, 2, 3, 0, 3, 1};

    glGenBuffers(1, &mesh->VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    mesh->ElementBuffer = sizeof(triangles) / sizeof(GLint);


    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
    bool done = false;

    
    //main loop
    while(!done) {

        glViewport(0, 0, screen_width, screen_height);

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                done = true;
            }
        }
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ElementBuffer);
        glDrawElements(GL_TRIANGLES, mesh->vertex_size, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        SDL_GL_SwapWindow(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();


}
