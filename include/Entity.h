#pragma once 
#include <Component.h>
#include <stdlib.h>

#define MAX_COMPONENTS 20

typedef struct _Entity {
    int id;
    int componentCount;
    Component components[MAX_COMPONENTS];
} Entity;

void addComponent(Entity* entity, ComponentType type, void* data); 
void* getComponent(Entity* entity, ComponentType type);
Animation* getAnimationComponent(Entity* entity, const char* animationName);