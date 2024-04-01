#include <Model.h>

static void sogv_vec3_lerp(vec3 from, vec3 to, float t, vec3 dest) {
    vec3 s, v;
    s[0] = s[1] = s[2] = t;
    vec3_sub(v, to, from);
    v[0] = s[0]*v[0];
    v[1] = s[1]*v[1];
    v[2] = s[2]*v[2];
    vec3_add(dest, from, v);
}

static void sogv_vec4_lerp(vec4 from, vec4 to, float t, vec4 dest) {
    vec4 s, v;
    s[0] = s[1] = s[2] = s[3] = t;
    vec4_sub(v, to, from);
    v[0] = s[0]*v[0];
    v[1] = s[1]*v[1];
    v[2] = s[2]*v[2];
    v[3] = s[3]*v[3];
    vec4_add(dest, from, v);
}

static void sogv_vec4_copy(vec4 from, vec4 to) {
    to[0] = from[0];
    to[1] = from[1];
    to[2] = from[2];
    to[3] = from[3];
}

static void sogv_quat_slerp(quat from, quat to, float t, quat dest) {
    vec4 q1, q2;
    float cos_theta, sin_theta, angle;

    cos_theta = from[0] * to[0] + from[1] * to[1] + from[2] * to[2] + from[3] * to[3];
    sogv_vec4_copy(from, q1);

    if(fabsf(cos_theta) >= 1.0f) {
        sogv_vec4_copy(q1, dest);
        return;
    }
    if(cos_theta < 0.0f) {
        q1[0] = -q1[0];
        q1[1] = -q1[1];
        q1[2] = -q1[2];
        q1[3] = -q1[3];
        cos_theta = -cos_theta;
    }

    sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

    if(fabsf(sin_theta) < 0.001f) {
        sogv_vec4_lerp(from, to, t, dest);
        return;
    }

    angle = acosf(cos_theta);
    vec4_scale(q1, q1, sinf((1.0f-t)*angle));
    vec4_scale(q2, to, sinf(t*angle));
    vec4_add(q1, q1, q2);
    vec4_scale(dest, q1, 1.0f/sin_theta);
}

static void sogv_assimp_vec3(vec3 vec, struct aiVector3D ai_vec) {
    vec[0] = ai_vec.x;
    vec[1] = ai_vec.y;
    vec[2] = ai_vec.z;
}

static void sogv_assimp_vec2(vec2 vec, struct aiVector3D ai_vec) {
    vec[0] = ai_vec.x;
    vec[1] = ai_vec.y;
}

static void sogv_assimp_quat(quat q, struct aiQuaternion ai_q) {
    q[0] = ai_q.x;
    q[1] = ai_q.y;
    q[2] = ai_q.z;
    q[3] = ai_q.w;
}

static void sogv_assimp_mat4x4(mat4x4 mat, struct aiMatrix4x4 ai_mat) {
    mat[0][0] = ai_mat.a1;
    mat[0][1] = ai_mat.b1;
    mat[0][2] = ai_mat.c1;
    mat[0][3] = ai_mat.d1;

    mat[1][0] = ai_mat.a2;
    mat[1][1] = ai_mat.b2;
    mat[1][2] = ai_mat.c2;
    mat[1][3] = ai_mat.d2;

    mat[2][0] = ai_mat.a3;
    mat[2][1] = ai_mat.b3;
    mat[2][2] = ai_mat.c3;
    mat[2][3] = ai_mat.d3;

    mat[3][0] = ai_mat.a4;
    mat[3][1] = ai_mat.b4;
    mat[3][2] = ai_mat.c4;
    mat[3][3] = ai_mat.d4;
}
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
    model->root_node = NULL;
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f}, model->position); /* Position set to 0 by default */
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
        const size_t ai_bone_count = scene->mMeshes[meshIndex]->mNumBones;
        Mesh* mesh = (Mesh *)calloc(1, sizeof(Mesh));
        MeshCreate(mesh, scene->mMeshes[meshIndex]);
        // Setup bones to a model
        if(ai_bone_count>0) {
            char bone_names[MAX_BONES][64];
            // go throught the ai_bone_count and see if we already have the same name inside our model
            // if we dont have the name: add; if we have - skip.
            for(size_t i=0; i<ai_bone_count; ++i) {
                const struct aiBone* ai_bone = scene->mMeshes[meshIndex]->mBones[i];
                strncpy(bone_names[i], ai_bone->mName.data, 63);

                bool exists = false;
                for(size_t j=0; j<MAX_BONES; ++j)
                    if(strcmp(bone_names[i], model->bone_names[j])==0) {
                        exists = true;
                        printf("bone %s is already saved", bone_names[i]);
                }

                if(!exists) {
                    sogv_assimp_mat4x4(model->bones[i], ai_bone->mOffsetMatrix);
                    strncpy(model->bone_names[i], bone_names[i], 63);
                    model->bone_count++;
                }

                // Setup bone weights
                const size_t ai_weight_count = ai_bone->mNumWeights;
                for(size_t j=0; j<ai_weight_count; ++j) {
                    struct aiVertexWeight ai_weight = ai_bone->mWeights[j];
                    unsigned int v_i = ai_weight.mVertexId;
                    for(size_t k=0; k<MAX_BONE_INFLUENCE; ++k) {
                        if(mesh->vertices[v_i].Weights[k]==0.0f) {
                            mesh->vertices[v_i].BoneInfo[k] = i;
                            mesh->vertices[v_i].Weights[k] = ai_weight.mWeight;
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

            printf("Model bone count: %zu\n", model->bone_count);
    for(size_t i=0; i<model->bone_count; ++i) printf("bone %zu : %s\n", i, model->bone_names[i]);

    // Setup skeleton nodes
    const struct aiNode* ai_node = scene->mRootNode;
    if(sogv_skel_node_import(ai_node, &model->root_node, model->bone_count, model->bone_names)==1)
        printf("No skeleton found inside the model\n");

    // Setup first animation
    printf("Number of animation : %d\n", scene->mNumAnimations);
    if(scene->mNumAnimations > 0) {
        const struct aiAnimation* anim = scene->mAnimations[0];
        printf("animation has a name: %s\n", anim->mName.data);
        printf("animation has %u nodechannels\n", anim->mNumChannels);
        printf("animation has %u meshchannels\n", anim->mNumMeshChannels);
        printf("animation is %f long\n", anim->mDuration);
        printf("animation has %f ticks per second\n", anim->mTicksPerSecond);
        model->anim_dur = anim->mDuration;
        model->anim_ticks = anim->mTicksPerSecond;

        for(size_t i=0; i<anim->mNumChannels; ++i) {
            const struct aiNodeAnim* channel = anim->mChannels[i];
            sogv_skel_node* node = sogv_skel_node_find(model->root_node, channel->mNodeName.data);
            node->pos_keys_count = channel->mNumPositionKeys;
            node->rot_keys_count = channel->mNumRotationKeys;
            node->sca_keys_count = channel->mNumScalingKeys;
            node->pos_keys = calloc(node->pos_keys_count, sizeof(vec3));
            node->rot_keys = calloc(node->rot_keys_count, sizeof(quat));
            node->sca_keys = calloc(node->sca_keys_count, sizeof(vec3));
            node->pos_key_times = calloc(node->pos_keys_count, sizeof(float));
            node->rot_key_times = calloc(node->rot_keys_count, sizeof(float));
            node->sca_key_times = calloc(node->sca_keys_count, sizeof(float));

            for(size_t j=0; j<node->pos_keys_count; ++j) {
                sogv_assimp_vec3(node->pos_keys[j], channel->mPositionKeys[j].mValue);
                node->pos_key_times[j] = channel->mPositionKeys[j].mTime;
            }

            for(size_t j=0; j<node->rot_keys_count; ++j) {
                sogv_assimp_quat(node->rot_keys[j], channel->mRotationKeys[j].mValue);
                node->rot_key_times[j] = channel->mRotationKeys[j].mTime;
            }

            for(size_t j=0; j<node->sca_keys_count; ++j) {
                sogv_assimp_vec3(node->sca_keys[j], channel->mScalingKeys[j].mValue);
                node->sca_key_times[j] = channel->mScalingKeys[j].mTime;
            }
        }
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
        struct aiColor4D color = {0.f,0.f,0.f, 0.f};
        if(aiGetMaterialColor(scene->mMaterials[materialIndex],AI_MATKEY_COLOR_SPECULAR,&color) == AI_SUCCESS){
            printf("Specular : %f,%f,%f,%f\n", color.r, color.g, color.b,color.a);

        }else{
            printf("yo bitvh");
        }

    }

    /* When the model is fully loaded we can release the data imported */
    aiReleaseImport(scene);
}

void ModelDraw(Model* model, Shader* shader, Camera* camera) {

    /* Before each render of our object we need to pass the model matrix on the shader */
    ModelMatrixCalculate(model->position, model->rotation, model->scale,camera,shader);

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
    mat4 modelMatrix;
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


sogv_skel_node* sogv_skel_node_find(sogv_skel_node* root, const char* name) {
    if(strcmp(name, root->name)==0)
        return root;

    for(size_t i=0; i<root->child_count; ++i) {
        sogv_skel_node* child = sogv_skel_node_find(root->children[i], name);
        if(child) return child;
    }

    return NULL;
}


int sogv_skel_node_import(const struct aiNode* ai_node, sogv_skel_node** skel_node,
                        size_t bone_count, char bone_names[][64]) {
    sogv_skel_node* t_node = calloc(1, sizeof(sogv_skel_node));
    t_node->bone_idx = -1;
    t_node->child_count = 0;
    t_node->pos_keys = NULL;
    t_node->rot_keys = NULL;
    t_node->sca_keys = NULL;
    t_node->pos_keys_count = 0;
    t_node->rot_keys_count = 0;
    t_node->sca_keys_count = 0;
    t_node->pos_key_times = NULL;
    t_node->rot_key_times = NULL;
    t_node->sca_key_times = NULL;
    strncpy(t_node->name, ai_node->mName.data, 63);
    printf("node name: %s\n", t_node->name);
    printf("ai_node has %u children\n", ai_node->mNumChildren);
    
    for(size_t i=0; i<MAX_BONES; ++i)
        t_node->children[i] = NULL;

    bool has_bone = false;
    for(size_t i=0; i<bone_count; ++i)
        if(strcmp(bone_names[i], t_node->name)==0) {
            printf("node will use bone %zu : %s\n", i, t_node->name);
            t_node->bone_idx = i;
            has_bone = true;
            break;
        }
    if(!has_bone) printf("no bones found\n");

    bool has_usable_child = false;
    for(size_t i=0; i<ai_node->mNumChildren; ++i) {
        if(sogv_skel_node_import(ai_node->mChildren[i],
                    &t_node->children[t_node->child_count], bone_count, bone_names)==0) {
            has_usable_child = true;
            t_node->child_count++;
        } else printf("non-usable child node thrown away\n");
    }
    if(has_usable_child || has_bone) {
        *skel_node = t_node;
        return 0;
    }

    free(t_node);
    t_node = NULL;
    return 1;
}

void sogv_skel_node_clean(sogv_skel_node* node) {
    if(node->pos_keys) free(node->pos_keys);
    if(node->rot_keys) free(node->rot_keys);
    if(node->sca_keys) free(node->sca_keys);
    if(node->pos_key_times) free(node->pos_key_times);
    if(node->rot_key_times) free(node->rot_key_times);
    if(node->sca_key_times) free(node->sca_key_times);
    for(size_t i=0; i<node->child_count; ++i)
        sogv_skel_node_clean(node->children[i]);
}


void sogv_skel_animate(sogv_skel_node* node, float anim_time, mat4x4 parent_mat, mat4x4* bones,
        mat4x4* bone_anim_mats) {
// our -> base animation; local -> matrix that moves;
    mat4x4 our_mat, local_anim_mat;
    mat4x4_dup(our_mat, parent_mat);
    mat4x4_identity(local_anim_mat);

    mat4x4 t_node;
    mat4x4_identity(t_node);
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
        vec3_dup(vi, node->pos_keys[p_key]);
        vec3_dup(vf, node->pos_keys[n_key]);
        vec3 lerp0, lerp1, lerp;
        vec3_scale(lerp0, vi, 1.0f-t);
        vec3_scale(lerp1, vf, t);
        vec3_add(lerp, lerp0, lerp1);
        mat4x4_translate_in_place(t_node, lerp[0], lerp[1], lerp[2]);
    }

    /*mat4x4 s_node;
    mat4x4_identity(s_node);
    if(node->sca_keys_count>0) {
        size_t p_key = 0;
        size_t n_key = 0;
        for(size_t i=0; i<node->sca_keys_count-1; ++i) {
            p_key = i;
            n_key = i+1;
            if(node->sca_key_times[n_key]>=anim_time) break;
        }
        float t_tot = node->sca_key_times[n_key] - node->sca_key_times[p_key];
        float t = (anim_time - node->sca_key_times[p_key]) / t_tot;
        vec3 vi, vf;
        vec3_dup(vi, node->sca_keys[p_key]);
        vec3_dup(vf, node->sca_keys[n_key]);
        vec3 lerp0, lerp1, lerp;
        vec3_scale(lerp0, vi, 1.0f-t);
        vec3_scale(lerp1, vf, t);
        vec3_add(lerp, lerp0, lerp1);
        mat4x4_translate_in_place(t_node, lerp[0], lerp[1], lerp[2]);
    }*/

    mat4x4 r_node;
    mat4x4_identity(r_node);
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
        quat vi, vf;
        vec4_dup(vi, node->rot_keys[p_key]);
        vec4_dup(vf, node->rot_keys[n_key]);
        quat lerp;
        sogv_quat_slerp(vi, vf, t, lerp);
        mat4x4_from_quat(r_node, lerp);
    }

    mat4x4_mul(local_anim_mat, t_node, r_node);
    // mat4x4_mul(local_anim_mat, local_anim_mat, s_node);

    int bone_i = node->bone_idx;
    if(bone_i > -1) {
        mat4x4 bone_offset;
        mat4x4_dup(bone_offset, bones[bone_i]);
        mat4x4_mul(our_mat, parent_mat, local_anim_mat);
        mat4x4 whatsthis;
        mat4x4_mul(whatsthis, our_mat, bone_offset);
        mat4x4_dup(bone_anim_mats[bone_i], whatsthis);
    }
    for(size_t i=0; i<node->child_count; ++i)
        sogv_skel_animate(node->children[i], anim_time, our_mat, bones, bone_anim_mats);
}