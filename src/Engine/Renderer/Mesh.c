#include <Mesh.h>
#include <SDL2/SDL.h>
#include <stdio.h>


void mesh_init(Mesh* model) {
	glGenVertexArrays(1, &(model->VAO));
	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->EBO));

}

void mesh_load(Mesh* model, GLfloat *vertices, GLuint *indices){
    glBindVertexArray(model->VAO);
    //Configure VBO
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * model->vertexCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
    //Configure EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
    //Not nessecary 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

Mesh* mesh_create(GLfloat* vertices, GLuint* indices, unsigned int vertexCount, unsigned int indexCount){

    Mesh* model = (Mesh*)malloc(sizeof(model));

	mesh_init(model);
	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_load(model, vertices, indices);

	return model;
}



void mesh_draw(Mesh* model) {
	glBindVertexArray(model->VAO);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}
