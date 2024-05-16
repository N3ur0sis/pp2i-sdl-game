#include <Collider.h>

Collider* ColliderCreate(const char* path){
    Collider* collider = (Collider*)malloc(sizeof(Collider));
    collider->numCollider = 0;
    struct aiScene* scene = ModelLoad(path);
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        if(i>=100){
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
    return collider;
}


void UpdateCollider(Collider* collider){
    for (size_t i = 0; i < collider->numCollider; i++)
    {
    glm_aabb_transform(collider->boundingBox[i],collider->transformMatrix,collider->boundingBox[i]);
    glm_aabb_transform(collider->boundingBoxReference[i],collider->transformMatrix,collider->boundingBoxReference[i]);
    }
}
