#include <Entity.h>

void addComponent(Entity* entity, uint32_t type, void* data) {
    if (entity->componentCount > MAX_COMPONENTS) {
        return; // Maximum components reached
    }
    entity->components[entity->componentCount].type = type;
    entity->components[entity->componentCount].data = data;
    entity->componentCount++;
}

void* getComponent(Entity* entity, ComponentType type) {
    for (int i = 0; i < entity->componentCount; ++i) {
        if (entity->components[i].type == type) {
            return entity->components[i].data;
        }
    }
    return NULL;
}

Animation* getAnimationComponent(Entity* entity, const char* animationName) {
    for (int i = 0; i < entity->componentCount; ++i) {
        if (entity->components[i].type == COMPONENT_ANIMATION) {
            Animation* animation = (Animation*)entity->components[i].data;
            if (strcmp(animation->name, animationName) == 0) {
                return animation;
            }
        }
    }
    return NULL; // Animation not found
    printf("Animation not found\n");
}