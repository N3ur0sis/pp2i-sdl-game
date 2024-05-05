#pragma once
#include <assimp/cimport.h>
#include <cglm/cglm.h>

void AssimpVec3(vec3 vec, struct aiVector3D ai_vec);
void AssimpQuat(versor q, struct aiQuaternion ai_q);
void AssimpMat4(mat4 mat, struct aiMatrix4x4 ai_mat);
