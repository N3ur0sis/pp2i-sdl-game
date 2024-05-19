#pragma once
#include <Model.h>

typedef struct _Collider{
    vec3 boundingBoxReference[100][2];
    vec3 boundingBox[100][2];
    mat4 transformMatrix;
    int numCollider;
} Collider;

Collider* ColliderCreate(const char* path);

void UpdateCollider(Collider* collider);

void FreeCollider(Collider* collider);