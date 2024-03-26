#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cglm/cglm.h>
#include <Shader.h>
#include <SDL2/SDL.h>
#include <Camera.h>
#include <Textures.h>

typedef struct _Vertex {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
} Vertex;

typedef struct _Texture {
    unsigned int id;
    char* type;
} Texture;  

typedef struct _MeshData {
    Vertex*       vertices;
    unsigned int* indices;
    size_t vertexCount, indiceCount, matID;
    GLuint VAO, VBO, EBO;
} MeshData;  

typedef struct _Model{
    MeshData* meshes;
    Texture* materials;
    size_t meshCount;
    size_t matCount;
    char* directory;
    vec3 posiiton;
    vec3 rotation;
    vec3 scale;
} Model;


MeshData* MeshCreate(Vertex* vertices, unsigned int* indices, Texture* textures);
void MeshDraw(Model* model,MeshData* mesh, Shader* shader, Camera* camera);
void MeshSetup(MeshData* mesh);

Model* ModelCreate(char* path);
void ModelDraw(Model* model, Shader* shader, Camera* camera);
void processNode(struct aiNode * node, const struct aiScene *scene, Model* model);
MeshData processMesh(struct aiMesh *mesh, const struct aiScene *scene);
Texture* loadMaterialTextures(struct aiMaterial *mat, enum aiTextureType type, char* typeName);
void calculateModelMatrix(vec3 position,vec3 rotation, vec3 scale , Camera* camera, Shader* sahder);