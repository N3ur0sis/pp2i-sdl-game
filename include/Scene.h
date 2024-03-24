#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cglm/cglm.h>
#include <Shader.h>
#include <SDL2/SDL.h>

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
    Texture*      textures;
    unsigned int VAO, VBO, EBO;
} MeshData;  

typedef struct _Model{
    MeshData* meshes;
    char* directory;


} Model;


MeshData* MeshCreate(Vertex* vertices, unsigned int* indices, Texture* textures);
void MeshDraw(Shader* shader);
void MeshSetup(MeshData* mesh);

Model* ModelCreate(char* path);
void ModelDraw(Shader* shader, MeshData* meshes);
void processNode(struct aiNode * node, const struct aiScene *scene, Model* model);
MeshData processMesh(struct aiMesh *mesh, const struct aiScene *scene);
Texture* loadMaterialTextures(struct aiMaterial *mat, enum aiTextureType type, char* typeName);