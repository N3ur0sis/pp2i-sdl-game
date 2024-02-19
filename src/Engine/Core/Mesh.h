#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

typedef struct _Mesh {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint  ElementBuffer;
    GLuint vertex_size;
} Mesh;


Mesh* init();
void draw(Mesh*);




#endif
