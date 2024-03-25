#include <Scene.h>


Model* ModelCreate(char* path){

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

    size_t meshCount = scene->mNumMeshes;
    size_t matCount = scene->mNumMaterials;
    //Setup the Model
    Model* model = calloc(1, sizeof(Model));
    model->meshes = calloc(meshCount, sizeof(MeshData));
    model->materials = calloc(matCount, sizeof(Texture));
    model->meshCount = meshCount;
    model->matCount = matCount; 

    model->directory = (char *)malloc(255);
    *model->directory = '\0';
    unsigned uiPathLength = 0;
    const char * p_cDirSlash = strrchr(path, '/');
    if (p_cDirSlash != NULL) {
        uiPathLength = (unsigned)(p_cDirSlash - path) + 1;;
        strncat(model->directory, path, uiPathLength);
    }

    for(size_t meshIDX = 0; meshIDX < meshCount; meshIDX++){

        const struct aiMesh* ai_mesh = scene->mMeshes[meshIDX];
        const size_t vertCount = ai_mesh->mNumVertices;
        const size_t faceCount = ai_mesh->mNumFaces;
        size_t indexCount = 0;

        MeshData mesh = {
            .vertices = calloc(vertCount, sizeof(Vertex)),
            .indices = NULL,
            .vertexCount = vertCount,
            .indiceCount = 0,
            .matID = ai_mesh->mMaterialIndex
        };

        //Copy vertex data
        for(size_t i = 0; i< vertCount; ++i){
            mesh.vertices[i].Position[0] = ai_mesh->mVertices[i].x;
            mesh.vertices[i].Position[1] = ai_mesh->mVertices[i].y;
            mesh.vertices[i].Position[2] = ai_mesh->mVertices[i].z;

            if(ai_mesh->mNormals){
                mesh.vertices[i].Normal[0] = ai_mesh->mNormals[i].x;
                mesh.vertices[i].Normal[1] = ai_mesh->mNormals[i].y;
                mesh.vertices[i].Normal[2] = ai_mesh->mNormals[i].z;
            }
            if(ai_mesh->mTextureCoords[0]){
                mesh.vertices[i].TexCoords[0] = ai_mesh->mTextureCoords[0][i].x;
                mesh.vertices[i].TexCoords[1] = ai_mesh->mTextureCoords[0][i].y;
            }
        }

        //count indices
        for(size_t i=0; i<faceCount; ++i){
            indexCount += ai_mesh->mFaces[i].mNumIndices;
        }

        //Set them up an copy
        mesh.indiceCount = indexCount;
        mesh.indices = calloc(indexCount, sizeof(unsigned int));

        {
            size_t iter = 0;
            for(size_t i=0; i<faceCount; ++i)
                for(size_t j=0; j<ai_mesh->mFaces[i].mNumIndices; ++j)
                    mesh.indices[iter++] = ai_mesh->mFaces[i].mIndices[j];
        }

        // Copy everything to GL buffers and put into model array
        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        glBindVertexArray( mesh.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh.vertexCount * sizeof(Vertex), mesh.vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indiceCount * sizeof(unsigned int), mesh.indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
        model->meshes[meshIDX] = mesh;
    }

        for(size_t m_idx = 0; m_idx < matCount; ++m_idx) {
        struct aiString ai_str;
        if(aiGetMaterialTexture(scene->mMaterials[m_idx], aiTextureType_DIFFUSE, 0, &ai_str,
                    NULL, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            char* tex_path = calloc(strlen(model->directory)+strlen(ai_str.data)+1, sizeof(char));
            strcpy(tex_path, model->directory);
            strcat(tex_path, ai_str.data);
            model->materials[m_idx].id = load_textures(tex_path);
            printf("%s, %ld, %ld\n", tex_path, matCount, m_idx);
            free(tex_path);
        }
        else{
            printf("unable to get material textures\n");
        }
    }
    aiReleaseImport(scene);
    return model;
}

void MeshDraw(MeshData* mesh, Shader* shader, Camera* camera) {
    mat4 modelMatrix;
    glm_mat4_identity(modelMatrix);
    vec3 rotAxis = {0.0f, 1.0f, 0.0f};
    glm_rotate(modelMatrix, glm_rad(0.0f), rotAxis);
    glUniformMatrix4fv(shader->m_locations.Model, 1, GL_FALSE, (float*)modelMatrix);
    glUniformMatrix4fv(shader->m_locations.View, 1, GL_FALSE, (float*)camera->viewMatrix);
    glUniformMatrix4fv(shader->m_locations.Projection, 1, GL_FALSE, (float*)camera->projectionMatrix);
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indiceCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void ModelDraw(Model* model, Shader* shader, Camera* camera) {
    for(size_t i=0; i<model->meshCount; ++i) {
        glBindTexture(GL_TEXTURE_2D, model->materials[model->meshes[i].matID].id);
        MeshDraw(&model->meshes[i], shader, camera);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
