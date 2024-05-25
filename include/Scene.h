#pragma once

#include <Shader.h>
#include <Skybox.h>
#include <Entity.h>
#include <GameState.h>

#define MAX_ENTITIES 100

#define INIT_SCENE(sceneVar, sceneManager, startFunc, updateFunc, unloadFunc) \
    Scene* sceneVar = (Scene*)calloc(1, sizeof(Scene)); \
    sceneVar->numEntities = 0; \
    SceneManagerAddScene(sceneManager, sceneVar, startFunc, updateFunc, unloadFunc);


typedef struct _Scene {
    Shader* shader;
    Shader* textShader;
    Skybox* skybox;
    Camera* camera;
    Entity entities[MAX_ENTITIES];
    int numEntities;
    float deltaTime;
    void (*start)(struct _Scene* scene, GameState* gameState);
    void (*update)(struct _Scene* scene, GameState* gameState);
    void (*unload)(struct _cene* scene);
} Scene;

Entity* createEntity(Scene* scene);

void freeScene(Scene* scene);
void* freeEntity(Entity* e); 