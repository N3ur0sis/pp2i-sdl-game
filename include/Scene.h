#pragma once

#include <Shader.h>
#include <Camera.h>
#include <Skybox.h>
#include <Entity.h>
#include <GameState.h>
#include <Dungeon.h>

#define MAX_ENTITIES 100

typedef struct _Scene {
    Shader* shader;
    Skybox* skybox;
    Camera* camera;
    Entity entities[MAX_ENTITIES];
    int numEntities;
    float deltaTime;
    void (*start)(struct _Scene* scene, GameState* gameState);
    void (*update)(struct _Scene* scene, GameState* gameState);
} Scene;

Entity* createEntity(Scene* scene);