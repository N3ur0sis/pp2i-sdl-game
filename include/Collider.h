#pragma once
#include <Model.h>
#define MAXCOLLIDER 1000
typedef struct _Collider{
    vec3 boundingBoxReference[MAXCOLLIDER][2];
    vec3 boundingBox[MAXCOLLIDER][2];
    mat4 transformMatrix;
    int numCollider;
    bool isCollidable;
} Collider;

Collider* ColliderCreate(char* path);

void UpdateCollider(Collider* collider);

void FreeCollider(Collider* collider);