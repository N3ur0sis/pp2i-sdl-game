#include <Model.h>



const struct aiScene* ModelLoad(char* path){
    
    /* Holds all the data like meshes, materials, animations */
    const struct aiScene *c_scene = aiImportFile(path,
    aiProcess_GenSmoothNormals |
    aiProcess_CalcTangentSpace |
    aiProcess_Triangulate |
    aiProcess_ImproveCacheLocality |
    aiProcess_SortByPType |
    aiProcess_GenBoundingBoxes);

    /* Always check if importation succeeded and if data is complete */
    if (!c_scene  || c_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !c_scene->mRootNode) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Failed to open scene file: %s\n", aiGetErrorString());
        return NULL;
    }
    return c_scene;
}

void ModelCreate(Model* model, char* path){

    /* Retreive data imported in assimp's format */
    const struct aiScene * scene = ModelLoad(path);
    
    /* Read data for initialization */
    size_t meshesCount = scene->mNumMeshes;
    size_t materialsCount = scene->mNumMaterials;

    /* Initialize the Model's member */
    model->meshes = (Mesh*)calloc(meshesCount, sizeof(Mesh));
    model->materials = (Texture*)calloc(materialsCount, sizeof(Texture));
    model->meshCount = meshesCount;
    model->matCount = materialsCount; 
    model->bone_count = 0;
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f}, model->position); /* Position set to 0 by default */
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f}, model->rotation); /* Rotation set to 0 by default */
    glm_vec3_copy((vec3){1.0f,1.0f,1.0f}, model->scale);    /* Scale    set to 1 by default*/
    /* We store the path to the model because every textures or animations related to it is stored on the same directory */
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

        /* Laoding vertices data like position, normals and uvs */
        Mesh* mesh = (Mesh *)calloc(1, sizeof(Mesh));
        MeshCreate(mesh, scene->mMeshes[meshIndex]);

        /* If the mesh have a rig we also want to load bone information of the model */
        const size_t boneCount = scene->mMeshes[meshIndex]->mNumBones;
        if(boneCount>0) {
            char boneNames[MAX_BONES][64];
            /* For each bone we check if we already have it on the model, otherwise we name it */
            for(size_t i=0; i<boneCount; ++i) {

                const struct aiBone* aiBone = scene->mMeshes[meshIndex]->mBones[i];
                memcpy(boneNames[i], aiBone->mName.data, 63);
                bool exists = false;
                for(size_t j=0; j<MAX_BONES; ++j)
                    if(strcmp(boneNames[i], model->bone_names[j])==0) {
                        exists = true;
                }
                /* For each bone we store the name and the offset Matrix related to it, we could create a struct for Bones */
                if(!exists) {
                    AssimpMat4(model->bones[i], aiBone->mOffsetMatrix);
                    memcpy(model->bone_names[i], boneNames[i], 63);
                    model->bone_count++;
                }

                /* We add weights information of each bone */
                const size_t weightCount = aiBone->mNumWeights;
                for(size_t j=0; j<weightCount; ++j) {
                    struct aiVertexWeight aiWeight = aiBone->mWeights[j];
                    unsigned int v_i = aiWeight.mVertexId;
                    for(size_t k=0; k<MAX_BONE_INFLUENCE; ++k) {
                        if(mesh->vertices[v_i].Weights[k]==0.0f) {
                            /* Id used by the shader to animate the model */
                            mesh->vertices[v_i].BoneInfo[k] = i;
                            mesh->vertices[v_i].Weights[k] = aiWeight.mWeight;
                            break;
                        }
                    }
                }
            }
        }

        /* We are ready to wrap data into GL buffers */
        MeshSetup(mesh);
        model->meshes[meshIndex] = *mesh;
        free(mesh);
    }
    


    /* For each material present in the model we want to load the corresponding textures*/
    for(size_t materialIndex = 0; materialIndex < materialsCount; ++materialIndex) {

        /* We only try to retreive the diffuse texture path*/
        struct aiString diffuseTex;
        if(aiGetMaterialTexture(scene->mMaterials[materialIndex], aiTextureType_DIFFUSE, 0, &diffuseTex, NULL, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            
            char* diffusePath = (char*)calloc(strlen(model->directory)+strlen(diffuseTex.data)+1, sizeof(char));
            strcpy(diffusePath, model->directory);
            strcat(diffusePath, diffuseTex.data);

            /* Load a image file and bind it to a texture ID */
            model->materials[materialIndex].id = TextureLoad(diffusePath);
            free(diffusePath);
        }
        /* Note: Sometimes assimp will load more materials than necessary hence the check for AI_SUCCESS */
    }

    /* When the model is fully loaded we can release the data imported */
    aiReleaseImport(scene);
}

void ModelDraw(Model* model, Shader* shader, Camera* camera) {

    /* Before each render of our object we need to pass the model matrix on the shader */
    ModelMatrixCalculate(model->position, model->rotation, model->scale,camera,shader, model->modelMatrix);

    /* We need to draw each mesh present in the model */
    for(size_t i=0; i<model->meshCount; ++i) {
        
        /* Each mesh is a part of the model but can use different texture for rendering*/
        glBindTexture(GL_TEXTURE_2D, model->materials[model->meshes[i].matID].id);
        MeshDraw(&model->meshes[i]);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void ModelMatrixCalculate(vec3 position,vec3 rotation, vec3 scale, Camera* camera, Shader* shader, mat4 modelMatrix ){

    /* Create a Scale matrix used to scale the model */
    mat4 scaleMatrix;
    glm_scale_make(scaleMatrix, scale);

    /* Create a translation matrix relative to the positon given in parameters */
    mat4 translateMatrix;
    glm_translate_make(translateMatrix, position);

    /* Represent rotation with quaternion, one for each axis */
    versor qx, qy, qz;
    glm_quat(qx,rotation[0], 1.0f, 0.0f,0.0f );
    glm_quat(qy,rotation[1], 0.0f, 1.0f,0.0f );
    glm_quat(qz,rotation[2], 0.0f, 0.0f,1.0f );

    /* Each quaternion quaternion are multiplied, rotation are applmied around  z,y and then x */
    glm_quat_mul(qx,qy,qx);
    glm_quat_mul(qx,qz,qz);

    /* Rotation matrix that hold the orientation of the object */
    mat4 rotationMatrix;
    glm_quat_mat4(qz,rotationMatrix);

    /** The model matrix, commbination of Translation, Rotation and Scaling.
     * Transform are applied in the order, scale, rotation and translate 
     */
    glm_mat4_mul(translateMatrix,rotationMatrix,modelMatrix);
    glm_mat4_mul(modelMatrix,scaleMatrix,modelMatrix);

    /* MVP matrices are sent to the shader*/
    glUniformMatrix4fv(shader->m_locations.Model, 1, GL_FALSE, (float*)modelMatrix);
    glUniformMatrix4fv(shader->m_locations.View, 1, GL_FALSE, (float*)camera->viewMatrix);
    glUniformMatrix4fv(shader->m_locations.Projection, 1, GL_FALSE, (float*)camera->projectionMatrix);
    glUniform3fv(shader->m_locations.cameraPosition,1,camera->Position);

}


void ModelFree(Model* model) {
    for(size_t i=0; i<model->meshCount; ++i)
        MeshClean(&model->meshes[i]);
    free(model->meshes);
    free(model->materials);
    free(model->directory);
    free(model);
    }




void ModelAnimate(Node* node, float anim_time, mat4 parent_mat, mat4* bones,
        mat4* bone_anim_mats) {
    // our -> base animation; local -> matrix that moves;
    mat4 our_mat, local_anim_mat;
    glm_mat4_dup(parent_mat,our_mat);
    glm_mat4_identity(local_anim_mat);

    mat4 t_node;
    glm_mat4_identity(t_node);
    if(node->pos_keys_count>0) {
        size_t p_key = 0;
        size_t n_key = 0;
        for(size_t i=0; i<node->pos_keys_count-1; ++i) {
            p_key = i;
            n_key = i+1;
            if(node->pos_key_times[n_key]>=anim_time) break;
        }
        float t_tot = node->pos_key_times[n_key] - node->pos_key_times[p_key];
        float t = (anim_time - node->pos_key_times[p_key]) / t_tot;
        vec3 vi, vf;
        glm_vec3_dup(node->pos_keys[p_key],vi );
        glm_vec3_dup(node->pos_keys[n_key],vf );
        vec3 lerp0, lerp1, lerp;
        glm_vec3_scale(vi, 1.0f-t,lerp0);
        glm_vec3_scale(vf,t,lerp1);
        glm_vec3_add(lerp0, lerp1,lerp);
        glm_translate(t_node, (vec3){lerp[0], lerp[1], lerp[2]});
    }

    /** Uncomment the following if you want to use scale animation
     *mat4 s_node;
     *glm_mat4_identity(s_node);
     *if(node->sca_keys_count>0) {
     *    size_t p_key = 0;
     *    size_t n_key = 0;
     *    for(size_t i=0; i<node->sca_keys_count-1; ++i) {
     *        p_key = i;
     *        n_key = i+1;
     *        if(node->sca_key_times[n_key]>=anim_time) break;
     *    }
     *    float t_tot = node->sca_key_times[n_key] - node->sca_key_times[p_key];
     *    float t = (anim_time - node->sca_key_times[p_key]) / t_tot;
     *    vec3 vi, vf;
     *    glm_vec3_dup(node->sca_keys[p_key], vi);
     *    glm_vec3_dup(node->sca_keys[n_key], vf);
     *    vec3 lerp0, lerp1, lerp;
     *    glm_vec3_scale(vi, 1.0f-t, lerp0);
     *    glm_vec3_scale(vf, t, lerp1);
     *    glm_vec3_add(lerp0, lerp1, lerp);
     *    glm_translate(t_node, (vec3){lerp[0], lerp[1], lerp[2]});
     *}
     */

    mat4 r_node;
    glm_mat4_identity(r_node);
    if(node->rot_keys_count>0) {
        size_t p_key = 0;
        size_t n_key = 0;
        for(size_t i=0; i<node->rot_keys_count-1; ++i) {
            p_key = i;
            n_key = i+1;
            if(node->rot_key_times[n_key]>=anim_time) break;
        }
        float t_tot = node->rot_key_times[n_key] - node->rot_key_times[p_key];
        float t = (anim_time - node->rot_key_times[p_key]) / t_tot;
        versor vi, vf;
        glm_vec4_dup(node->rot_keys[p_key],vi);
        glm_vec4_dup(node->rot_keys[n_key],vf);
        versor lerp;
        glm_quat_slerp(vi, vf, t, lerp);
        glm_quat_mat4(lerp,r_node);
    } 

    glm_mat4_mul(t_node, r_node,local_anim_mat);
    /* Uncomment if you want scaling interpolation */
    /* glm_mat4_mul(local_anim_mat, s_node,local_anim_mat); */

    int bone_i = node->bone_idx;
    if(bone_i > -1) {
        mat4 bone_offset;
        glm_mat4_dup(bones[bone_i], bone_offset);
        glm_mat4_mul(parent_mat, local_anim_mat, our_mat);
        mat4 whatsthis;
        glm_mat4_mul(our_mat, bone_offset, whatsthis);
        glm_mat4_dup(whatsthis,bone_anim_mats[bone_i]);
    }
    for(size_t i=0; i<node->child_count; ++i)
        ModelAnimate(node->children[i], anim_time, our_mat, bones, bone_anim_mats);
}

