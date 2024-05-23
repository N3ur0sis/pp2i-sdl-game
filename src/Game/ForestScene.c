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
    float x;
    float y;
    float z;
    float rot;
    switch (gameState->previousSceneIndex){
        case(1) ://from dungeon
            x = -6.0;
            y = 10.1;
            z = 168.0;
            rot = glm_rad(180.0f);
            break;
        default :
            x = 1.0;
            y = 10.1;
            z = 3.0;
            rot = 0;
            break;
    }
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");
    UseShaders(scene->shader);
    /* Create a scene camera */
    scene->camera = camera_create(x, y+5, z, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, 1.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Map Entity */
    Entity* mapEntity = createEntity(scene);
    if (mapEntity != NULL) {
        Model* map = (Model*)calloc(1, sizeof(Model));
        ModelCreate(map,"assets/models/Foret/forest.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        Collider* mapCollision = ColliderCreate("assets/models/Foret/col.obj");//Create a .obj file for this scene
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -1.0f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Player Entity */
    Entity* playerEntity = create_player(scene,x,y,z);
    Model* playerModel = getComponent(playerEntity,COMPONENT_RENDERABLE);
    playerModel->rotation[1] = rot;

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
    Entity* golem = create_golem(scene,0.0f,0.1f,0.0f,0.5f);

    /*Flame Entity*/
    Entity* flame1 = createEntity(scene);
    if (flame1){
        Model* flame = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame->isRenderable = false;
         }  
        glm_vec3_copy((vec3){50.5f,9.8f,112.0f},flame->position);
        addComponent(flame1, COMPONENT_RENDERABLE, flame);
        
    }
    Entity* flame2 = createEntity(scene);
    if (flame2){
        Model* flame_2 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_2, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_2->isRenderable = false;
         }  
        glm_vec3_copy((vec3){62.3f,9.8f,156.0f},flame_2->position);
        addComponent(flame2, COMPONENT_RENDERABLE, flame_2);
        
    }
    Entity* flame3 = createEntity(scene);
    if (flame3){
        Model* flame_3 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_3, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_3->isRenderable = false;
         }  
        glm_vec3_copy((vec3){-59.0f,9.8f,146.50f},flame_3->position);
        addComponent(flame3, COMPONENT_RENDERABLE, flame_3);
        
    }
    Entity* flame4 = createEntity(scene);
    if (flame4){
        Model* flame_4 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_4, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_4->isRenderable = false;
         }   
        glm_vec3_copy((vec3){-64.7f,9.8f,72.0f},flame_4->position);
        addComponent(flame4, COMPONENT_RENDERABLE, flame_4);
        
    }
    
    

}
void updateForestScene(Scene* scene, GameState* gameState){
    // Game Logic
    bool isClicking = false;
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
        if (!playerModel->isBusy){
            playerMovement(playerEntity, scene->deltaTime, scene->camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));
        }
    }
    if (getKeyState(SDLK_p)){
        printf("Player Position : %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    /*Four flames logic */
    SDL_Color color_black = {0, 0, 0, 0};
    Entity* flame1 = &scene->entities[5];
    Model* flame1Model = (Model*)getComponent(flame1, COMPONENT_RENDERABLE);
    Entity* flame2 = &scene->entities[6];
    Model* flame2Model = (Model*)getComponent(flame2, COMPONENT_RENDERABLE);
    Entity* flame3 = &scene->entities[7];
    Model* flame3Model = (Model*)getComponent(flame3, COMPONENT_RENDERABLE);
    Entity* flame4 = &scene->entities[8];
    Model* flame4Model = (Model*)getComponent(flame4, COMPONENT_RENDERABLE);
    if (!flame1Model->isRenderable){
        float d1 = getDist(playerModel,flame1Model);
        if ((d1<FLAMEDIST&&getKeyState(SDLK_e))){
            flame1Model->isRenderable = true;
            playerModel->isBusy = true;
            
        }
    }
    if (!flame2Model->isRenderable){
        float d2 = getDist(playerModel,flame2Model);
        if ((d2<FLAMEDIST&&getKeyState(SDLK_e))){
            flame2Model->isRenderable = true;
            playerModel->isBusy = true;  
        }
        
    }
    if (!flame3Model->isRenderable){
        float d3 = getDist(playerModel,flame3Model);
        if ((d3<FLAMEDIST&&getKeyState(SDLK_e))){
            flame3Model->isRenderable = true;
            playerModel->isBusy = true;
            
        }
    }
    if (!flame4Model->isRenderable){
         float d4 = getDist(playerModel,flame4Model);
         if ((d4<FLAMEDIST&&getKeyState(SDLK_e))){
            flame4Model->isRenderable = true;
            playerModel->isBusy = true;
            
        }
    }
    if (playerModel->isBusy ){
        RenderText("Vous entendez un bruit sourd au loin", color_black, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 100, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1)){
            playerModel->isBusy = false;
        }
    }
    vec3 DonjonPosition ;
    vec3 DonjonDir;
    glmc_vec3_copy((vec3){-7.4f,10.0f, 168.69f},DonjonPosition);
    glm_vec3_sub( playerModel->position, DonjonPosition, DonjonDir);
    float DonjonDist = glm_vec3_norm(DonjonDir);
    if (DonjonDist<1.0f&&getKeyState(SDLK_e) &&flame1Model->isRenderable&&flame2Model->isRenderable&&flame3Model->isRenderable&&flame4Model->isRenderable){
        gameState->change = true;
        gameState ->nextSceneIndex = 1;
        gameState->previousSceneIndex = 2;
    }

}

void unloadForestScene(Scene* scene){
    DeleteShaders(scene->shader);
    DeleteShaders(scene->textShader);
    SkyboxDelete(scene->skybox);

    if (scene->camera) {
        free(scene->camera);
    }

    for (int i = 0; i < scene->numEntities; i++) {
        freeEntity(&scene->entities[i]);
    }
    scene->numEntities = 0;
}