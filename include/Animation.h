#pragma once
#include <Model.h>

typedef struct Animation {
    Node* root_node;
    mat4 parent_mat;
    mat4* bone_mats;
    mat4* bone_anim_mats;
    float anim_dur;
    float anim_ticks;
} Animation;

Animation* AnimationCreate(char* path, Model* model);
void CalculateBoneTransformation(Node* node, float anim_time, mat4 parent_mat, mat4* bones,mat4* bone_anim_mats);

Node* NodeFind(Node* root, const char* name);
int NodeImport(const struct aiNode* ai_node, Node** skel_node, size_t bone_count, char bone_names[][128]);
void NodeDelete(Node* node);
