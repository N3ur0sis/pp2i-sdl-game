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
