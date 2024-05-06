#include <Animation.h>


Animation* AnimationCreate(char* path, Model* model){

    Animation* anim = calloc(1, sizeof(Animation));
    const struct aiScene *scene = ModelLoad(path);
    // Setup skeleton nodes
    const struct aiNode* ai_node = scene->mRootNode;
    if(NodeImport(ai_node, &anim->root_node, model->bone_count, model->bone_names)==1)
        printf("No skeleton found inside the model\n");
    
    // Setup first animation
    //printf("Number of animation : %d\n", scene->mNumAnimations);
    if(scene->mNumAnimations > 0) {
        const struct aiAnimation*aiAnim = scene->mAnimations[0];
        anim->anim_dur = aiAnim->mDuration;
        anim->anim_ticks = aiAnim->mTicksPerSecond;
        for(size_t i=0; i<aiAnim->mNumChannels; ++i) {
            const struct aiNodeAnim* channel = aiAnim->mChannels[i];
            Node* node = NodeFind(anim->root_node, channel->mNodeName.data);
            node->pos_keys_count = channel->mNumPositionKeys;
            node->rot_keys_count = channel->mNumRotationKeys;
            node->sca_keys_count = channel->mNumScalingKeys;
            node->pos_keys = calloc(node->pos_keys_count, sizeof(vec3));
            node->rot_keys = calloc(node->rot_keys_count, sizeof(versor));
            node->sca_keys = calloc(node->sca_keys_count, sizeof(vec3));
            node->pos_key_times = calloc(node->pos_keys_count, sizeof(float));
            node->rot_key_times = calloc(node->rot_keys_count, sizeof(float));
            node->sca_key_times = calloc(node->sca_keys_count, sizeof(float));

            for(size_t j=0; j<node->pos_keys_count; ++j) {
                AssimpVec3(node->pos_keys[j], channel->mPositionKeys[j].mValue);
                node->pos_key_times[j] = channel->mPositionKeys[j].mTime;
            }

            for(size_t j=0; j<node->rot_keys_count; ++j) {
                AssimpQuat(node->rot_keys[j], channel->mRotationKeys[j].mValue);
                node->rot_key_times[j] = channel->mRotationKeys[j].mTime;
            }

            for(size_t j=0; j<node->sca_keys_count; ++j) {
                AssimpVec3(node->sca_keys[j], channel->mScalingKeys[j].mValue);
                node->sca_key_times[j] = channel->mScalingKeys[j].mTime;
            }
        }
    }

    
    anim->bone_anim_mats = calloc(MAX_BONES, sizeof(mat4));
    for(size_t i=0; i<MAX_BONES; ++i){
        glm_mat4_identity(anim->bone_anim_mats[i]);

    }
    aiReleaseImport(scene);
    return anim;
}

Node* NodeFind(Node* root, const char* name) {
    if(strcmp(name, root->name)==0)
        return root;

    for(size_t i=0; i<root->child_count; ++i) {
        Node* child = NodeFind(root->children[i], name);
        if(child) return child;
    }

    return NULL;
}


int NodeImport(const struct aiNode* ai_node, Node** skel_node, size_t bone_count, char bone_names[][128]) {
    Node* t_node = calloc(1, sizeof(Node));
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
    memcpy(t_node->name, ai_node->mName.data, 127);
    //printf("node name: %s\n", t_node->name);
    //printf("ai_node has %u children\n", ai_node->mNumChildren);
    
    for(size_t i=0; i<MAX_BONES; ++i)
        t_node->children[i] = NULL;

    bool has_bone = false;
    for(size_t i=0; i<bone_count; ++i)
        if(strcmp(bone_names[i], t_node->name)==0) {
            //printf("node will use bone %zu : %s\n", i, t_node->name);
            t_node->bone_idx = i;
            has_bone = true;
            break;
        }
    //if(!has_bone) printf("no bones found\n");

    bool has_usable_child = false;
    for(size_t i=0; i<ai_node->mNumChildren; ++i) {
        if(NodeImport(ai_node->mChildren[i],
                    &t_node->children[t_node->child_count], bone_count, bone_names)==0) {
            has_usable_child = true;
            t_node->child_count++;
        } //else printf("non-usable child node thrown away\n");
    }
    if(has_usable_child || has_bone) {
        *skel_node = t_node;
        return 0;
    }

    free(t_node);
    t_node = NULL;
    return 1;
}

void NodeDelete(Node* node) {
    if(node->pos_keys) free(node->pos_keys);
    if(node->rot_keys) free(node->rot_keys);
    if(node->sca_keys) free(node->sca_keys);
    if(node->pos_key_times) free(node->pos_key_times);
    if(node->rot_key_times) free(node->rot_key_times);
    if(node->sca_key_times) free(node->sca_key_times);
    for(size_t i=0; i<node->child_count; ++i)
        NodeDelete(node->children[i]);
}

void CalculateBoneTransformation(Node* node, float anim_time, mat4 parent_mat, mat4* bones,mat4* bone_anim_mats){
    
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