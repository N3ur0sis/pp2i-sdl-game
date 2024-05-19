#include <Scene.h>
Entity* createEntity(Scene* scene) {
    if (scene->numEntities >= MAX_ENTITIES) {
        return NULL; // Maximum entities reached
    }
    Entity* entity = &scene->entities[scene->numEntities++];
    entity->id = scene->numEntities;
    entity->componentCount = 0;
    return entity;
}

void freeDungeonScene(Scene* scene){
    free(scene->camera);
    DeleteShaders(scene->shader);
    SkyboxDelete(scene->skybox);
    free(scene->entities);
    free(scene);
}

void* freeEntity(Entity* e){
    
}