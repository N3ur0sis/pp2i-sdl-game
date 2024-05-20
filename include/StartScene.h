#pragma once
#include <Scene.h>
#include <Player.h>
#include <GameState.h>
#include <cglm/cglm.h>
#include "Ennemy.h"


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
    Entity* golem = create_golem(scene);

    /* Player Entity */
    Entity* playerEntity = create_player(scene,28.0f,0.1f,7.0f);

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
}
 
void updateMainScene(Scene* scene, GameState* gameState) {
    // Game Logic
    Entity* playerEntity = &scene->entities[1];
    Entity* enemy = &scene->entities[0];
    Entity* mapEntity = &scene->entities[3];

    if (playerEntity && enemy) {
        Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
        Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
        Collider* playerCollider = (Collider*)getComponent(playerEntity, COMPONENT_COLLIDER);

        Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
        Animator* enemyAnimator = (Animator*)getComponent(enemy, COMPONENT_ANIMATOR);


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
}

void unloadStartScene(Scene* scene){
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