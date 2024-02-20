#include <Mesh.h>
#include <SDL2/SDL.h>
#include <stdio.h>

    Mesh* init(){
    
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

    return mesh;
    }

    void draw(Mesh* mesh){
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->VertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ElementBuffer);
        glDrawElements(GL_TRIANGLES, mesh->vertex_size, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
    }
    
