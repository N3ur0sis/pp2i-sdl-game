#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>

bool checkpoint_sword = false;
int click_counter = 0 ;
bool is_clicking = false;

void startMainScene(Scene* scene, GameState* gameState) {
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");
    /* Create a scene camera */
    scene->camera = camera_create(28, 5, 10, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    /* Enemy Entity */
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
        golem->isRenderable = false;
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

    /* Player Entity */
    Entity* playerEntity = createEntity(scene);
    if (playerEntity != NULL) {
        Model* playerModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(playerModel, "assets/models/LoPotitChat/PlayerWalk.dae");
        Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerAttack.dae", playerModel, "playerAttackAnimation");
        Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerWalk.dae", playerModel, "playerWalkingAnimation");
        Animation* iddleAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerIdle.dae", playerModel, "playerIdleAnimation");
        Animation* runningAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerRunning.dae", playerModel, "playerRunningAnimation");
        Animator* playerAnimator = AnimatorCreate(walkingAnimation);
        glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, playerModel->scale);
        RigidBody* playerRigidBody = (RigidBody*)calloc(1,sizeof(RigidBody));
        glm_vec3_copy((vec3){28.0f, 0.1f, 7.0f}, playerRigidBody->velocity);
        playerRigidBody->speed = .0f;
        Collider* playerCollider = ColliderCreate("assets/models/LoPotitChat/PlayerWalk.dae");
        glm_scale_make(playerCollider->transformMatrix, (vec3){0.5f, 0.5f, 0.5f});
        UpdateCollider(playerCollider);

        addComponent(playerEntity, COMPONENT_RENDERABLE, playerModel);
        addComponent(playerEntity, COMPONENT_ANIMATION, attackAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, walkingAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, iddleAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, runningAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATOR, playerAnimator);
        addComponent(playerEntity, COMPONENT_COLLIDER, playerCollider);
        addComponent(playerEntity, COMPONENT_RIGIDBODY, playerRigidBody);
    }

    /* Sword Entity */
    Entity* swordEntity = createEntity(scene);
    if (swordEntity != NULL) {
        Model* sword = (Model*)calloc(1, sizeof(Model));
        ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
        sword->isRenderable = false;
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


    /* Map Entity */
    Entity* mapEntity = createEntity(scene);
    if (mapEntity != NULL) {
        Model* map = (Model*)calloc(1, sizeof(Model));
        ModelCreate(map, "assets/models/start/start.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        Collider* mapCollision = ColliderCreate("assets/models/start/col.obj");
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -1.0f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Chest Entity */
    Entity* chestEntity = createEntity(scene);
    if (chestEntity != NULL) {
        Model* chestClose = (Model*)calloc(1, sizeof(Model));
        ModelCreate(chestClose, "assets/models/Objet/Chest/ChestFerme.obj");
        glm_vec3_copy((vec3){-0.2f,1.2f,-33.3f},chestClose->position);
        addComponent(chestEntity, COMPONENT_RENDERABLE, chestClose);
        Collider* chestCollision = ColliderCreate("assets/models/Objet/Chest/ChestFerme.obj");
        glm_translate_make(chestCollision->transformMatrix, (vec3){-0.2f, 1.2f, -33.3f});
        UpdateCollider(chestCollision);
        addComponent(chestEntity, COMPONENT_COLLIDER, chestCollision);
    }
    Entity* chestOpenEntity = createEntity(scene);
    if (chestOpenEntity != NULL) {
        Model* chestOpen = (Model*)calloc(1, sizeof(Model));
        ModelCreate(chestOpen, "assets/models/Objet/Chest/ChestOuvert.obj");
        glm_vec3_copy((vec3){-0.2f,1.2f,-33.4f},chestOpen->position);
        chestOpen->isRenderable = false;
        addComponent(chestOpenEntity, COMPONENT_RENDERABLE, chestOpen);
    }
}

void updateMainScene(Scene* scene, GameState* gameState) {

    
    // Game Logic
    Entity* enemy = &scene->entities[0];
    Entity* playerEntity = &scene->entities[1];
    Entity* swordEntity = &scene->entities[2];
    Entity* mapEntity = &scene->entities[3];
    Entity* chestEntity = &scene->entities[5];
    Entity* chestOpenEntity = &scene->entities[6];

    bool isBusy = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy;
    float x = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[0];
    float y = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[2];
    float z = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[1];
    printf("%f,%f,%f\n", scene->camera->Yaw,scene->camera->Pitch,scene->camera->Position[2]);

    if (playerEntity && enemy) {
        Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
        Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
        Collider* playerCollider = (Collider*)getComponent(playerEntity, COMPONENT_COLLIDER);
        RigidBody* playerRigidbody = (RigidBody*)getComponent(playerEntity, COMPONENT_RIGIDBODY);
        Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
        Animator* enemyAnimator = (Animator*)getComponent(enemy, COMPONENT_ANIMATOR);


        /* Game Logic */
        float rotTarget = 0.0f;
        vec3 enemyDir;
        glm_vec3_sub(playerModel->position, enemyModel->position, enemyDir);
        float enemyDist = glm_vec3_norm(enemyDir);
        glm_vec3_normalize(enemyDir);
        if(checkpoint_sword){
        if (enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f) {
            float omega = acos(glm_dot((vec3){0, 0, 1}, enemyDir));
            if (enemyDir[0] < 0) {
                omega = -omega;
            }
            if (getMouseButtonState(1) && !gameState->playerIsAttacking && !is_clicking) {
                gameState->playerIsAttacking = true;
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation");
                playerAnimator->playTime = 0.0f;
            } else if (!gameState->playerIsAttacking) {
                if(playerRigidbody->speed == 8.0f){
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerRunningAnimation");
                }else if(playerRigidbody->speed == 5.0f){
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerWalkingAnimation");
                }
            }
                        if (!getMouseButtonState(1)) {
                        is_clicking = false;
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
            playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerIdleAnimation");
        }
                if (y < -29.25f) {
            ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[1] = 1.1f;
        } else {
            ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[1] = 0.1f;
        }
        if (!isBusy) {
            playerMovement(playerEntity, scene->deltaTime, scene->camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));
        }
    }else{
                        if(playerRigidbody->speed == 8.0f){
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerRunningAnimation");
                }else if(playerRigidbody->speed == 5.0f){
                playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerWalkingAnimation");
                }
                        if (y < -29.25f) {
            ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[1] = 1.1f;
        } else {
            ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[1] = 0.1f;
        }
                        if (!isBusy) {
            playerMovement(playerEntity, scene->deltaTime, scene->camera, NULL);
        }
    }
        SDL_Color color_black = {0, 0, 0, 0};
        SDL_Color color_white = {255, 255, 255, 0};
        if ((x < 8.0f) && x > 3.5f && (y < 10.0f) && y > 5.5f && !isBusy) {            
            RenderText("Appuyer sur E pour interagir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            if (getKeyState(SDLK_e)) {
                isBusy = true;     
                ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy = true;
            }
        } else if ((x < 8.0f) && x > 3.5f && (y < 10.0f) && y > 5.5f && isBusy) {
            switch (click_counter) {
                case 0:
                    RenderText("Panneau étrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Bienvenue sur l'île oubliée voyageur!   ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Fais attention à toi sur cette île      ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter++;
                        is_clicking = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
                    break;
                case 1:
                    RenderText("Panneau etrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Bienvenue jeune aventurier !            ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Profite bien de cette superbe aventure !", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter++;
                        is_clicking = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
                    break;
                case 2:
                    RenderText("Panneau etrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Bienvenue jeune aventurier !            ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Profite bien de cette superbe aventure !", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter = 0;
                        isBusy = false;
                        ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy = false;
                        is_clicking = true;

                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
            }
            playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerIdleAnimation");
        }




        if(y < -30.5f && y > -35.5f && x < 2.08f && x > -2.8 && !isBusy && !checkpoint_sword){
            RenderText("Appuyer sur E pour interagir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            if (getKeyState(SDLK_e)) {
                isBusy = true;     
                ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy = true;
                glm_vec3_copy((vec3){-7.72,4.02,-37.04}, scene->camera->Position);
                scene->camera->Yaw = 40.0f;
                scene->camera->Pitch = -20.0f;
            }
        }else if (y < -30.5f && y > -35.5f && x < 2.08f && x > -2.8 && isBusy && !checkpoint_sword) {
            switch (click_counter) {
                case 0:
                    RenderText("Coffre         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Tu as trouvé une vielle épée en bois    ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Elle pourra servir dans le futur...     ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter = 0;
                        isBusy = false;
                        ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy = false;
                        ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = true;
                        ((Model*)getComponent(chestEntity, COMPONENT_RENDERABLE))->isRenderable = false;
                        ((Model*)getComponent(chestOpenEntity, COMPONENT_RENDERABLE))->isRenderable = true;
                        enemyModel->isRenderable = true;
                        is_clicking = true;
                        checkpoint_sword = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
            }
            playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerIdleAnimation");
        }

    }
}

