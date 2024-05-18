#pragma once

#include <Shader.h>
#include <Camera.h>
#include <Skybox.h>
#include <Entity.h>

#define MAX_ENTITIES 100

typedef struct _Scene {
    Shader* shader;
    Skybox* skybox;
    Camera* camera;
    Entity entities[MAX_ENTITIES];
    int numEntities;
    float deltaTime;
} Scene;

Entity* createEntity(Scene* scene);