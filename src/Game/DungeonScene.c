#include "DungeonScene.h"


/*
Entity of this scene (order of their index):
    Light
    Dungeon
    Player
    Sword
    Enemy
*/

void DungeonMainScene(Scene* scene, GameState* gameState) {
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
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
    Entity* enemy = &scene->entities[4];
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
        playerMovement(playerEntity, scene->deltaTime, scene->camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));
    if (getKeyState(SDLK_b)){
        printf("La direction d'ou on vient est %c, et %d et l id est %d\n",dj->direction,dj->current_room,dj->rooms[dj->current_room].id);
    }
    if (getKeyState(SDLK_p)){
        printf("Le joueur est en %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    switch(dj->rooms[dj->current_room].id){
        case 0:
        LogicRoom1C(dj,body );
        break;
        case 1:
        LogicRoom2C(dj,body );
        break;
        case 2:
        LogicRoom2I(dj,body );
        break;
        case 3:
        LogicRoom2L(dj,body );
        break;
        case 4:
        LogicRoom3C(dj,body );
        break;
        case 5:
        LogicRoom3T(dj,body );
        break;
        case 6:
        LogicRoom4C(dj,body );
        break;
        case 7:
        LogicRoomB(dj,body);
        break;
    }
    if (dj->change){
            dj->lastRoomChangeTime = SDL_GetTicks();
            LoadRoom(playerModel,dj,body, playerCollider,gameState);
            dj->change = false;
        }

}