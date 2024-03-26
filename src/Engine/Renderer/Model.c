#include <Model.h>

const struct aiScene* ModelLoad(char* path){
    
    /* Holds all the data like meshes, materials, animations */
    const struct aiScene *c_scene = aiImportFile(path,
    aiProcess_GenSmoothNormals |
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_ImproveCacheLocality |
    aiProcess_SortByPType);

    /* Always check if importation succeeded and if data is complete */
    if (!c_scene  || c_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !c_scene->mRootNode) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to open scene file: %s\n", aiGetErrorString());
        return NULL;
    }
    return c_scene;
}

Model* ModelCreate(char* path){

    /* Retreive data imported in assimp's format */
    const struct aiScene * scene = ModelLoad(path);
    
    /* Read data for initialization */
    size_t meshesCount = scene->mNumMeshes;
    size_t materialsCount = scene->mNumMaterials;

    /* Initialize the Model's member */
    Model* model = calloc(1, sizeof(Model));
    model->meshes = calloc(meshesCount, sizeof(Mesh));
    model->materials = calloc(materialsCount, sizeof(Texture));
    model->meshCount = meshesCount;
    model->matCount = materialsCount; 
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f}, model->posiiton); /* Position set to 0 by default */
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f}, model->rotation); /* Rotation set to 0 by default */
    glm_vec3_copy((vec3){1.0f,1.0f,1.0f}, model->scale);    /* Scale    set to 1 by default*/
    model->directory = (char *)malloc(255);
    *model->directory = '\0';
    unsigned pathLenght = 0;
    const char* slash = strrchr(path, '/');
    if (slash != NULL) {
        pathLenght = (unsigned)(slash - path) + 1;
        strncat(model->directory, path, pathLenght);
    }
    /* For each mesh present in the model we want to load data into GL buffers */
    for(size_t meshIndex = 0; meshIndex < meshesCount; meshIndex++){
        Mesh* mesh = MeshCreate(scene->mMeshes[meshIndex]);
        model->meshes[meshIndex] = *mesh;
    }

    /* For each material present in the model we want to load the corresponding textures*/
    for(size_t materialIndex = 0; materialIndex < materialsCount; ++materialIndex) {

        /* We only try to retreive the diffuse texture path*/
        struct aiString diffuseTex;
        if(aiGetMaterialTexture(scene->mMaterials[materialIndex], aiTextureType_DIFFUSE, 0, &diffuseTex, NULL, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {

            char* diffusePath = calloc(strlen(model->directory)+strlen(diffuseTex.data)+1, sizeof(char));
            strcpy(diffusePath, model->directory);
            strcat(diffusePath, diffuseTex.data);

            /* Load a image file and bind it to a texture ID */
            model->materials[materialIndex].id = load_textures(diffusePath);
            free(diffusePath);
        }
        /* Note: Sometimes assimp will load more materials than necessary hence the check for AI_SUCCESS */
    }

    /* When the model is fully loaded we can release the data imported */
    aiReleaseImport(scene);
    return model;
}

void ModelDraw(Model* model, Shader* shader, Camera* camera) {

    /* Before each render of our object we need to pass the model matrix on the shader */
    ModelMatrixCalculate(model->posiiton, model->rotation, model->scale,camera,shader);

    /* We need to draw each mesh present in the model */
    for(size_t i=0; i<model->meshCount; ++i) {
        
        /* Each mesh is a part of the model but can use different texture for rendering*/
        glBindTexture(GL_TEXTURE_2D, model->materials[model->meshes[i].matID].id);
        MeshDraw(&model->meshes[i]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void ModelMatrixCalculate(vec3 position,vec3 rotation, vec3 scale, Camera* camera, Shader* shader ){

    /* Create a Scale matrix used to scale the model */
    mat4 scaleMatrix;
    glm_scale_make(scaleMatrix, scale);

    /* Create a translation matrix relative to the positon given in parameters */
    mat4 translateMatrix;
    glm_translate_make(translateMatrix, position);

    /* Represent rotation with quaternion, one for each axis */
    versor qx, qy, qz;
    glm_quat(qx,rotation[0], 1.0f, 0.0f,0.0f );
    glm_quat(qy,rotation[0], 0.0f, 1.0f,0.0f );
    glm_quat(qz,rotation[0], 0.0f, 0.0f,1.0f );

    /* Each quaternion quaternion are multiplied, rotation are applmied around  z,y and then x */
    glm_quat_mul(qx,qy,qx);
    glm_quat_mul(qx,qz,qz);

    /* Rotation matrix that hold the orientation of the object */
    mat4 rotationMatrix;
    glm_quat_mat4(qz,rotationMatrix);

    /** The model matrix, commbination of Translation, Rotation and Scaling.
     * Transform are applied in the order, scale, rotation and translate 
     */
    mat4 modelMatrix;
    glm_mat4_mul(translateMatrix,rotationMatrix,modelMatrix);
    glm_mat4_mul(modelMatrix,scaleMatrix,modelMatrix);

    /* MVP matrices are sent to the shader*/
    glUniformMatrix4fv(shader->m_locations.Model, 1, GL_FALSE, (float*)modelMatrix);
    glUniformMatrix4fv(shader->m_locations.View, 1, GL_FALSE, (float*)camera->viewMatrix);
    glUniformMatrix4fv(shader->m_locations.Projection, 1, GL_FALSE, (float*)camera->projectionMatrix);

}
