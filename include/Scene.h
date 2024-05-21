#pragma once

#include <Shader.h>
#include <Camera.h>
#include <Skybox.h>
#include <Entity.h>
#include <GameState.h>

#define MAX_ENTITIES 100

typedef struct _Scene {
    Shader* shader;
    Shader* textShader;
    Shader* textShader;
    Skybox* skybox;
    Camera* camera;
    Entity entities[MAX_ENTITIES];
    int numEntities;
    float deltaTime;
    void (*start)(struct _Scene* scene, GameState* gameState);
    void (*update)(struct _Scene* scene, GameState* gameState);
    void (*unload)(struct Scene* scene);
} Scene;

Entity* createEntity(Scene* scene);

void freeScene(Scene* scene);
void* freeEntity(Entity* e); 