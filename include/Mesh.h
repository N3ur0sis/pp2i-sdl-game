#pragma once
#include <glad/glad.h>
#include <Shader.h>
#include <Camera.h>
#include <SDL2/SDL.h>
#include <Time.h>
#include <stdio.h>

typedef struct transformationMatrices {
	mat4 rotate;
	mat4 translate;
	mat4 scale;
	mat4 transform;
} meshTransformationMatrices;

typedef struct _Mesh {
	GLuint VAO;	// VERTEX ARRAY OBJECT
	GLuint VBO[3];	// VERTEX BUFFER OBJECT
	GLuint EBO;	// ELEMENT BUFFER OBJECT
	unsigned int vertexCount;
	unsigned int indexCount;
	unsigned int textureID;

	meshTransformationMatrices matrices;
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
void mesh_load(Mesh* model, GLfloat *vertices, GLuint *indices, GLfloat* texCoord, GLfloat* normals);
//Pulbic Methods :
Mesh*       mesh_create(GLfloat *vertices, GLfloat* texCoord, GLfloat* normals, GLuint *indices, unsigned int vertexCount, unsigned int indexCount);
void        mesh_draw(Mesh* model, Shader* s, Camera* c, Time* time);


void mesh_rotate(Mesh *model, bool x, bool y, bool z, float angle);
void mesh_resetRotation(Mesh *model);
void mesh_translate(Mesh *model, float x, float y, float z);
void mesh_resetTranslation(Mesh *model);
void mesh_scale(Mesh *model, float x, float y, float z);
void mesh_resetScaling(Mesh *model);

void mesh_updateTransformationMatrix(Mesh *model);
