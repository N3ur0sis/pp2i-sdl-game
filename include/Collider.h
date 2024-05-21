#pragma once
#include <Model.h>

typedef struct _Collider{
    vec3 boundingBoxReference[100][2];
    vec3 boundingBox[100][2];
    mat4 transformMatrix;
    int numCollider;
    bool isCollidable;
} Collider;

Collider* ColliderCreate(char* path);

void UpdateCollider(Collider* collider);