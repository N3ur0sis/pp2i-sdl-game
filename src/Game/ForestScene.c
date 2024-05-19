#include "ForestScene.h"


/*
Entity of this scene (order of their index):
    Light
    Map
    Player
    Sword
    Enemy
    Flame 1
    Flame 2
    Flame 3
    Flame 4
*/


void ForestMainScene(Scene* scene, GameState* gameState){
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

    /* Map Entity */
    Entity* mapEntity = createEntity(scene);
    if (mapEntity != NULL) {
        Model* map = (Model*)calloc(1, sizeof(Model));
        ModelCreate(map, "assets/models/Foret/forest.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        Collider* mapCollision = ColliderCreate("assets/models/start/col.obj");//Create a .obj file for this scene
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -1.0f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Player Entity */
    Entity* playerEntity = create_player(scene,1.0f,10.0f,3.0f);

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
    Entity* golem = create_golem(scene);

    /*Flame Entity*/
    Entity* flame1 = createEntity(scene);
    if (flame1){
        Model* flame = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame, "assets/models/Foret/Flame.obj");
        glm_vec3_copy((vec3){50.5f,9.8f,112.0f},flame->position);
        addComponent(flame1, COMPONENT_RENDERABLE, flame);
        
    }
    Entity* flame2 = createEntity(scene);
    if (flame2){
        Model* flame_2 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_2, "assets/models/Foret/Flame.obj");
        glm_vec3_copy((vec3){62.3f,9.8f,156.0f},flame_2->position);
        addComponent(flame2, COMPONENT_RENDERABLE, flame_2);
        
    }
    Entity* flame3 = createEntity(scene);
    if (flame3){
        Model* flame_3 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_3, "assets/models/Foret/Flame.obj");
        glm_vec3_copy((vec3){-59.0f,9.8f,146.50f},flame_3->position);
        addComponent(flame3, COMPONENT_RENDERABLE, flame_3);
        
    }
    Entity* flame4 = createEntity(scene);
    if (flame4){
        Model* flame_4 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_4, "assets/models/Foret/Flame.obj");
        glm_vec3_copy((vec3){-64.7f,9.8f,72.0f},flame_4->position);
        addComponent(flame4, COMPONENT_RENDERABLE, flame_4);
        
    }
    

}
void updateForestScene(Scene* scene, GameState* gameState){
    // Game Logic
    Entity* playerEntity = &scene->entities[2];
    Entity* enemy = &scene->entities[4];
    Entity* mapEntity = &scene->entities[1];

    Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
    Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
    Collider* playerCollider = (Collider*)getComponent(playerEntity, COMPONENT_COLLIDER);

    Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
    Animator* enemyAnimator = (Animator*)getComponent(enemy, COMPONENT_ANIMATOR);
    if (playerEntity && enemy) {


        /* Game Logic */
        float rotTarget = 0.0f;
        vec3 enemyDir;
        glm_vec3_sub(playerModel->position, enemyModel->position, enemyDir);
        float enemyDist = glm_vec3_norm(enemyDir);
        glm_vec3_normalize(enemyDir);
        if (enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f) {
            float omega = acos(glm_dot((vec3){0, 0, 1}, enemyDir));
            if (enemyDir[0] < 0) {
                omega = -omega;
            }
            if (getMouseButtonState(1) && !gameState->playerIsAttacking) {
                gameState->playerIsAttacking = true;
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation");
                playerAnimator->playTime = 0.0f;
            } else if (!gameState->playerIsAttacking) {
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerWalkingAnimation");
            }
            if (playerAnimator->playTime > playerAnimator->currentAnimation->anim_dur - 10 && gameState->playerIsAttacking) {
                gameState->playerIsAttacking = false;
                playerAnimator->playTime = 0.0f;
            }
            float currentAngleDeg = glm_deg(((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->rotation[1]);
            float targetAngleDeg = glm_deg(omega);
            while (targetAngleDeg - currentAngleDeg > 180) {
                targetAngleDeg -= 360;
            }
            while (targetAngleDeg - currentAngleDeg < -180) {
                targetAngleDeg += 360;
            }
            rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);
        }
        if (enemyDist < 3.0f) {
            if (!gameState->enemyIsAttacking) {
                gameState->enemyIsAttacking = true;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime = 0.0f;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemPunchAnimation");
            }
            if (((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime > ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation->anim_dur - 10) {
                gameState->playerHealth -= 10.0f;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime = 0.0f;
                gameState->enemyIsAttacking = false;
            }
            ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->rotation[1] = glm_rad(rotTarget);
        } else if (enemyDist < 15.0f) {
            ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->rotation[1] = glm_rad(rotTarget);
            gameState->enemyIsAttacking = false;
            ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemWalkingAnimation");
            glm_vec3_scale(enemyDir, 2 * scene->deltaTime, enemyDir);
            glm_vec3_add(((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->position, enemyDir, ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->position);
        } else {
            gameState->enemyIsAttacking = false;
            ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemIdleAnimation");
        }

        if(!((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || playerAnimator->currentAnimation == (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation"))){
            playerAnimator->playTime = 0.0f;
        }
        playerMovement(playerEntity, scene->deltaTime, scene->camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));
    }
    if (getKeyState(SDLK_p)){
        printf("Player Position : %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    vec3 DonjonPosition ;
    vec3 DonjonDir;
    glmc_vec3_copy((vec3){-7.4f,10.0f, 168.69f},DonjonPosition);
    glm_vec3_sub( playerModel->position, DonjonPosition, DonjonDir);
    float DonjonDist = glm_vec3_norm(DonjonDir);
    if (DonjonDist<1.0f&&getKeyState(SDLK_e)){
        gameState->change = true;
        gameState ->nextSceneIndex = 1;
    }
}
