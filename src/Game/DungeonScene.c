#include "DungeonScene.h"


/*
Entity of this scene (order of their index):
    Light
    Dungeon
    Player
    Sword
    KeyBossChest
    Chest
    Enemy
*/

void DungeonMainScene(Scene* scene, GameState* gameState) {
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");
    /* Create a scene camera */
    scene->camera = camera_create(28, 5, 10, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Dungeon Entity */
    Entity* dungeon = createEntity(scene);
    if (dungeon){
        Dungeon* dj = dj_create();
        initialize(dj);
        initializeRooms(dj);
        setTypeRoom(dj);
        Affiche(dj);
        addComponent(dungeon, COMPONENT_DUNGEON, dj);
    }

    /* Player Entity */
    Entity* playerEntity = createEntity(scene);
    if (playerEntity != NULL) {
        Model* playerModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(playerModel, "assets/models/LoPotitChat/PlayerWalk.dae");
        Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerAttack.dae", playerModel, "playerAttackAnimation");
        Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerWalk.dae", playerModel, "playerWalkingAnimation");
        Animator* playerAnimator = AnimatorCreate(walkingAnimation);
        glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, playerModel->scale);
        RigidBody* playerRigidBody = (RigidBody*)calloc(1,sizeof(RigidBody));
        playerRigidBody->speed = .0f;
        Collider* playerCollider = ColliderCreate("assets/models/LoPotitChat/PlayerWalk.dae");
        glm_scale_make(playerCollider->transformMatrix, (vec3){0.5f, 0.5f, 0.5f});
        UpdateCollider(playerCollider);

        addComponent(playerEntity, COMPONENT_RENDERABLE, playerModel);
        addComponent(playerEntity, COMPONENT_ANIMATION, attackAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, walkingAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATOR, playerAnimator);
        addComponent(playerEntity, COMPONENT_COLLIDER, playerCollider);
        addComponent(playerEntity, COMPONENT_RIGIDBODY, playerRigidBody);
    }

    /* Sword Entity */
    Entity* swordEntity = createEntity(scene);
    if (swordEntity != NULL) {
        Model* sword = (Model*)calloc(1, sizeof(Model));
        ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
        addComponent(swordEntity, COMPONENT_RENDERABLE, sword);

        // Adding attachment component to the sword entity
        AttachmentComponent* swordAttachment = (AttachmentComponent*)calloc(1, sizeof(AttachmentComponent));
        swordAttachment->boneIndex = 21; // Example bone index
        swordAttachment->parentAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
        swordAttachment->parentModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
        glm_vec3_copy((vec3){-1.3f, -0.7f, 0.3f}, swordAttachment->offsetPosition);
        glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, swordAttachment->offsetRotation);
        glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, swordAttachment->offsetScale);
        addComponent(swordEntity, COMPONENT_ATTACHMENT, swordAttachment);
    }
    

    /*KeyBossChest Entity*/
    Entity* keyBossChest = createEntity(scene);
    if (keyBossChest != NULL) {
        Model* keyBossChestModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(keyBossChestModel, "assets/models/Objet/Chest/ChestFermeSerrure.obj");
        addComponent(keyBossChest, COMPONENT_RENDERABLE, keyBossChestModel);
        keyBossChestModel->isRenderable = false;
        Model* keyBossChestOuvertModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(keyBossChestOuvertModel, "assets/models/Objet/Chest/ChestOuvert.obj");
        addComponent(keyBossChest, COMPONENT_RENDERABLE, keyBossChestOuvertModel);
        keyBossChestOuvertModel->isRenderable = false;
        Collider* keyBossChestCollider = ColliderCreate("assets/models/Objet/Chest/ChestOuvert.obj");
        glm_scale_make(keyBossChestCollider->transformMatrix, (vec3){0.5f, 0.5f, 0.5f});
        UpdateCollider(keyBossChestCollider);
        addComponent(keyBossChest, COMPONENT_COLLIDER, keyBossChestCollider);
    }
    /*Chest Entity*/
    Entity* Chest = createEntity(scene);
    if (Chest != NULL) {
        Model* ChestModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(ChestModel, "assets/models/Objet/Chest/ChestFermeSerrure.obj");
        addComponent(Chest, COMPONENT_RENDERABLE, ChestModel);
        ChestModel->isRenderable = false;
        Model* ChestOuvertModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(ChestOuvertModel, "assets/models/Objet/Chest/ChestOuvert.obj");
        addComponent(Chest, COMPONENT_RENDERABLE, ChestOuvertModel);
        ChestOuvertModel->isRenderable = false;
        Collider* ChestCollider = ColliderCreate("assets/models/Objet/Chest/ChestOuvert.obj");
        glm_scale_make(ChestCollider->transformMatrix, (vec3){0.5f, 0.5f, 0.5f});
        UpdateCollider(ChestCollider);
        addComponent(Chest, COMPONENT_COLLIDER, ChestCollider);
    }

    /* Enemy Entity */
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
        addComponent(enemy, COMPONENT_RENDERABLE, golem);

        Animation* golemIdleAnimation = AnimationCreate("assets/models/Golem/Mutant Breathing Idle.dae", golem, "golemIdleAnimation");
        Animation* golemWalkingAnimation = AnimationCreate("assets/models/Golem/Mutant Walking.dae", golem, "golemWalkingAnimation");
        Animation* golemPunchAnimation = AnimationCreate("assets/models/Golem/Mutant Punch.dae", golem, "golemPunchAnimation");
        Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemWalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemPunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);
        glm_vec3_copy((vec3){2.0f, 0.0f, -10.0f}, golem->position);
    }
}

void updateDungeonScene(Scene* scene, GameState* gameState) {
    Entity* playerEntity = &scene->entities[2];
    Entity* dungeon = &scene->entities[1];
    Entity* enemy = &scene->entities[5];
    Dungeon* dj = (Dungeon*)getComponent(dungeon, COMPONENT_DUNGEON);

    Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
    RigidBody* body = (Model*)getComponent(playerEntity, COMPONENT_RIGIDBODY);
    Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
    Collider* playerCollider = (Collider*)getComponent(playerEntity, COMPONENT_COLLIDER);
    Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
    Animator* enemyAnimator = (Animator*)getComponent(enemy, COMPONENT_ANIMATOR);
    if(!((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || playerAnimator->currentAnimation == (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation"))){
            playerAnimator->playTime = 0.0f;
        }
        if (!playerModel->isBusy){
        playerMovement(playerEntity, scene->deltaTime, scene->camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));}
    if (getKeyState(SDLK_b)){
        printf("La direction d'ou on vient est %c, et %d et l id est %d\n",dj->direction,dj->current_room,dj->rooms[dj->current_room].id);
    }
    if (getKeyState(SDLK_p)){
        printf("Le joueur est en %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    char *l = "NSWE";
    bool dir_used[4] = {false,false,false,false};
    for (int k=0;k<dj->nb_rooms;k++){
        if (dj->adj[dj->current_room][k]!='O'){
            for (int j=0;j<4;j++){
                if (dj->adj[dj->current_room][k]==l[j]){
                    dir_used[j]=true;
                }
            }
        }
    }
    SDL_Color color_black = {0,0,0,0};
    if (playerModel->isBusy && !dj->hasKey ){
        RenderText("La porte est fermée... Il me faudrait une clé pour l'ouvrir !", color_black, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 100, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1)){
            playerModel->isBusy = false;
        }
        }
    switch(dj->rooms[dj->current_room].id){
        case 0:
        LogicRoom1C(scene,gameState,dj,body);
        break;
        case 1:
        LogicRoom2C(scene,gameState,dj,body);
        break;
        case 2:
        LogicRoom2I(scene,gameState,dj,body);
        break;
        case 3:
        LogicRoom2L(scene,gameState,dj,body);
        break;
        case 4:
        LogicRoom3C(scene,gameState,dj,body);
        break;
        case 5:
        LogicRoom3T(scene,gameState,dj,body);
        break;
        case 6:
        LogicRoom4C(scene,gameState,dj,body);
        break;
        case 7:
        LogicRoomB(scene,gameState,dj,body);
        break;
    }
    
    if (dj->change){
            dj->lastRoomChangeTime = SDL_GetTicks();
            LoadRoom(scene,playerModel,dj,body, playerCollider,gameState);
            dj->change = false;
            if (dj->rooms[dj->current_room].type!=1){
                Entity* keyBossChest = &scene->entities[4];
                ((Model*)keyBossChest->components[1].data)->isRenderable = false;
                ((Model*)keyBossChest->components[0].data)->isRenderable = false;      
            }
        }

}

void unloadDungeonScene(Scene* scene){
    DeleteShaders(scene->shader);
    SkyboxDelete(scene->skybox);

    if (scene->camera) {
        free(scene->camera);
    }

    for (int i = 0; i < scene->numEntities; i++) {
        freeEntity(&scene->entities[i]);
    }
    scene->numEntities = 0;
}