#pragma once
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cglm/cglm.h>
#include <glad/glad.h>

#define MAX_BONES 50
#define MAX_BONE_INFLUENCE 4

/* A Custom vertex struct we pass to OpenGL */
typedef struct _Vertex {
    vec3 Position;          /* Posiiton of each vertex in the local space                   */
    vec3 Normal;            /* Normal direction of each vertex for lighting calculation     */
    vec2 TexCoords;         /* 2D coordinates in the correpsonding textures for this vertex */
    GLuint BoneInfo[MAX_BONE_INFLUENCE];
    float Weights[MAX_BONE_INFLUENCE];
} Vertex;


/* A Mesh class that hold data parsed from a file and converted ot OpenGL format*/
typedef struct _Mesh {
    Vertex*       vertices;           /* Arrays of vertex each contains posiiton, uvs and normals      */
    unsigned int* indices;            /* Arrays of indices to indicate wich vertices goes in each face */
    size_t vertexCount, indiceCount;  /* Numbers of vertex and indices of the mesh, used to know the size of the arrays */
    size_t matID;                     /* ID of the materials for this mesh in the arrays of materials available in the model */
    GLuint VAO, VBO, EBO;             /* GL Buffers to store vertex and indices and organise them in a VAO*/
} Mesh;  

/**
 * A constructor for the mesh class. It copies the data from an assimp mesh format
 * Into our OpenGL-friendly mesh format.
 * 
 * @param aiMesh A mesh extracted from an assimp scene object.
 * @return A Mesh object with all necessary data for rendering
 * and converted into proper format.
*/
void MeshCreate(Mesh* mesh, struct aiMesh* aiMesh);

/**
 * Auxiliary function used to GL-ize our Mesh object. Basically generate the buffers,
 * load data into them and specifies the arrays attribute (positon, normal and uvs).
 * @param mesh A mesh object ready to have buffers.
 * @note More attribute can be loaded into the VBO if needed.
*/
void MeshSetup(Mesh* mesh);

/**
 * Render the corresponding mesh using glDrawElements and bind the proper texture
 * associated with this mesh.
 * @param mesh A mesh ready to be rendered.
*/
void MeshDraw(Mesh* mesh);



void MeshClean(Mesh* mesh);


