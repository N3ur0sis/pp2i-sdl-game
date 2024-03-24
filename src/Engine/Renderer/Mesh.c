#include <Mesh.h>




void mesh_init(Mesh* model) {
	glGenVertexArrays(1, &(model->VAO));
	glGenBuffers(1, &(model->VBO[0]));
	glGenBuffers(1, &(model->VBO[1]));
	glGenBuffers(1, &(model->VBO[2]));
	glGenBuffers(1, &(model->EBO));
    glGenTextures(1, &model->textureID);

	glm_mat4_identity(model->matrices.rotate);
	glm_mat4_identity(model->matrices.translate);
	glm_mat4_identity(model->matrices.scale);
}

void mesh_load(Mesh* model, GLfloat *vertices, GLuint *indices, GLfloat* texCoord, GLfloat* normals){
    glBindVertexArray(model->VAO);
    //Configure VBO
    glBindBuffer(GL_ARRAY_BUFFER, model->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * model->indexCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, model->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * model->indexCount * sizeof(GLfloat), texCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, model->VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 3 * model->indexCount * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(2);
    //Configure EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
    //Not nessecary 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

Mesh* mesh_create(GLfloat* vertices, GLfloat* texCoord, GLfloat* normals, GLuint* indices, unsigned int vertexCount, unsigned int indexCount){

    Mesh* model = (Mesh*)malloc(sizeof(Mesh));

	mesh_init(model);
	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_load(model, vertices, indices, texCoord, normals);

	return model;
}



void mesh_draw(Mesh* model, Shader* shader, Camera* camera, Time* time) {
    (void)time;

	mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    vec3 rotAxis = {0.0f, 1.0f, 0.0f};
    glm_rotate(modelMatrix, glm_rad(0.0f), rotAxis);
    glUniformMatrix4fv(shader->m_locations.Model, 1, GL_FALSE, (float*)modelMatrix);
    glUniformMatrix4fv(shader->m_locations.View, 1, GL_FALSE, (float*)camera->viewMatrix);
    glUniformMatrix4fv(shader->m_locations.Projection, 1, GL_FALSE, (float*)camera->projectionMatrix);
	glBindVertexArray(model->VAO);
	glDrawArrays(GL_TRIANGLES, 0, model->indexCount);
}