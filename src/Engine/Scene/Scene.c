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


void freeScene(Scene* scene) {
    if (scene == NULL) return;

    DeleteShaders(scene->shader);
    SkyboxDelete(scene->skybox);

    if (scene->camera) {
        free(scene->camera);
    }

    for (int i = 0; i < scene->numEntities; i++) {
        freeEntity(&scene->entities[i]);
    }

    free(scene);
}


void* freeEntity(Entity* e){
    if (e == NULL) return;
    printf("id = %d\n",e->id);
    // Free each component, if it exists
    void* component = getComponent(e, COMPONENT_RENDERABLE);
    if (component){ 
        ModelFree((Model*)component);
        printf("Model free\n");}

    component = getComponent(e, COMPONENT_ANIMATION);
    if (component){
        AnimationDelete((Animation*)component);
        printf("Animation free\n");}

    component = getComponent(e, COMPONENT_ANIMATOR);
    if (component){
        FreeAnimator((Animator*)component);
        printf("Animator free\n");}

    component = getComponent(e, COMPONENT_COLLIDER);
    if (component){
        FreeCollider((Collider*)component);
        printf("Collider free\n");}

    component = getComponent(e, COMPONENT_LIGHT);
    if (component){
        free((Light*)component);
        printf("Light free\n");}

    component = getComponent(e, COMPONENT_ATTACHMENT);
    if (component){
        FreeAttachementComponent((AttachmentComponent*)component);
        printf("Attached free\n");}

    component = getComponent(e, COMPONENT_RIGIDBODY);
    if (component){
        FreeRigidBody((RigidBody*)component);
        printf("Body free\n");}

    component = getComponent(e, COMPONENT_DUNGEON);
    if (component){
        freeDungeon((Dungeon*)component);
        printf("Dungeon free\n");}
}

