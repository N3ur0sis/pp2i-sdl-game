#pragma once
#include <glad/glad.h>
#include <Shader.h>
#include <Camera.h>
#include <SDL2/SDL.h>
#include <Time.h>
#include <stdio.h>

typedef struct _Mesh {
	GLuint VAO;	// VERTEX ARRAY OBJECT
	GLuint VBO;	// VERTEX BUFFER OBJECT
	GLuint EBO;	// ELEMENT BUFFER OBJECT
	unsigned int vertexCount;
	unsigned int indexCount;
} Mesh;


/* How mesh works :
 * GENEARATE VAO
 * GENERATE BUFFERS
 * BIND THE VAO
 * BIND EACH BUFFER
 * SEND DATA FOR THE CURRENTLY BOUND BUFFER
 * DEFINE PARAMETERS OF EACH ATTRIBUTE
 * UNBIND VAO
 */


//Private Methods :
void mesh_init(Mesh*);
void mesh_load(Mesh* model, GLfloat *vertices, GLuint *indices);
//Pulbic Methods :
Mesh*       mesh_create(GLfloat *vertices, GLuint *indices, unsigned int vertexCount, unsigned int indexCount);
void        mesh_draw(Mesh* model, Shader* s, Camera* c, Time* time);
