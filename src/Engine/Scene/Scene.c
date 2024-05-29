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
    DeleteShaders(scene->textShader);
    SkyboxDelete(scene->skybox);
    free(scene->camera);


    for (int i = 0; i < scene->numEntities; i++) {
        freeEntity(&scene->entities[i]);
    }

    free(scene);
}


void* freeEntity(Entity* e){
    if (e == NULL) return;
    for (int i = 0; i < e->componentCount; i++)
    {
    // Free each component, if it exists
    Component component = e->components[i];
    if (component.type == COMPONENT_RENDERABLE){ 
        ModelFree((Model*)component.data);
        printf("Model free\n");}

    if (component.type == COMPONENT_ANIMATION){
        AnimationDelete((Animation*)component.data);
        printf("Animation free\n");}

    if (component.type == COMPONENT_ANIMATOR){
        FreeAnimator((Animator*)component.data);
        printf("Animator free\n");}

    if (component.type == COMPONENT_COLLIDER){
        FreeCollider((Collider*)component.data);
        printf("Collider free\n");}

    if (component.type == COMPONENT_LIGHT){
        DeleteShaders(((Light*)component.data)->shadowMap->shadowMapShader);
        free(((Light*)component.data)->shadowMap);
        free((Light*)component.data);
        printf("Light free\n");}

    if (component.type == COMPONENT_ATTACHMENT){
        FreeAttachementComponent((AttachmentComponent*)component.data);
        printf("Attached free\n");}

    if (component.type == COMPONENT_RIGIDBODY){
        FreeRigidBody((RigidBody*)component.data);
        printf("Body free\n");
    }
    if(component.type == COMPONENT_ENEMY){
        free(component.data);
    }
    if(component.type == COMPONENT_PLAYER){
        free(component.data);
    }
    if(component.type == COMPONENT_DUNGEON){
        free(component.data);
    }}
}
