#include <Scene.h>


MeshData* MeshCreate(Vertex* vertices, unsigned int* indices, Texture* textures){
    MeshData* mesh = (MeshData*)malloc(sizeof(MeshData));
    mesh->vertices = vertices;
    mesh->indices = indices;
    mesh->textures = textures;
    MeshSetup(mesh);
    return mesh;
}

void MeshSetup(MeshData* mesh){
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);
  
    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), &mesh->vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices) * sizeof(unsigned int), 
                 &mesh->indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void MeshDraw(Shader* shader){
    (void)shader;
}


void ModelDraw(Shader* shader, MeshData* meshes)
{
    (void)meshes;
        MeshDraw(shader);
}

Model* ModelCreate(char* path){

    Model *model = (Model*)malloc(sizeof(Model));

    const struct aiScene * scene = aiImportFile(path,
    aiProcess_GenSmoothNormals |
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_ImproveCacheLocality |
    aiProcess_SortByPType);

    // Check if import failed
    if (!scene  || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to open scene file: %s\n", aiGetErrorString());
        return false;
    }
    model->meshes = (MeshData*)malloc(scene->mNumMeshes * sizeof(MeshData));
    model->directory = (char*)malloc(255);
    // Get import file base path
    unsigned pathLength = 0;
    const char * dirSlash = strrchr(path, '/');
    if (dirSlash != NULL) {
        pathLength = (unsigned)(dirSlash - path) + 1;
        strncat(model->directory, path, pathLength);
    }
    processNode(scene->mRootNode, scene, model);

    return model;
}

void processNode(struct aiNode * node, const struct aiScene *scene, Model* model){
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        struct aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        model->meshes[i] = processMesh(mesh, scene);			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, model);
    }
}

MeshData processMesh(struct aiMesh *mesh, const struct aiScene *scene){
    (void)mesh;
    (void)scene;
    MeshData meshes = { 0 };
    return meshes;
}