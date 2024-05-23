#include <Collider.h>

Collider* ColliderCreate(char* path){
    Collider* collider = (Collider*)malloc(sizeof(Collider));
    collider->numCollider = 0;
    glm_mat4_identity(collider->transformMatrix);
    const struct aiScene* scene = ModelLoad(path);
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        if(i>=MAXCOLLIDER){
            break;
        }

    glm_vec3_copy((vec3){scene->mMeshes[i]->mAABB.mMin.x,
        				 scene->mMeshes[i]->mAABB.mMin.y,
        				 scene->mMeshes[i]->mAABB.mMin.z},  collider->boundingBoxReference[i][0]);
    glm_vec3_copy((vec3){scene->mMeshes[i]->mAABB.mMax.x,
    
        				 scene->mMeshes[i]->mAABB.mMax.y,
        				 scene->mMeshes[i]->mAABB.mMax.z}, collider->boundingBoxReference[i][1]);
	glm_vec3_copy(collider->boundingBoxReference[i][0], collider->boundingBox[i][0]);
	glm_vec3_copy(collider->boundingBoxReference[i][1], collider->boundingBox[i][1]);
    collider->numCollider++;
    }
    
    aiReleaseImport(scene);
    collider->isCollidable = true;
    return collider;
}


void UpdateCollider(Collider* collider){
    for (int i = 0; i < collider->numCollider; i++)
    {
    glm_aabb_transform(collider->boundingBox[i],collider->transformMatrix,collider->boundingBox[i]);
    glm_aabb_transform(collider->boundingBoxReference[i],collider->transformMatrix,collider->boundingBoxReference[i]);
    }
}

void FreeCollider(Collider* collider){
    free(collider);
}