#include <Algebra.h>


void AssimpVec3(vec3 vec, struct aiVector3D ai_vec) {
    vec[0] = ai_vec.x;
    vec[1] = ai_vec.y;
    vec[2] = ai_vec.z;
}


void AssimpQuat(versor q, struct aiQuaternion ai_q) {
    q[0] = ai_q.x;
    q[1] = ai_q.y;
    q[2] = ai_q.z;
    q[3] = ai_q.w;
}

void AssimpMat4(mat4 mat, struct aiMatrix4x4 ai_mat) {
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