#include "Enemy.h"


bool isDamageShown = false;
void initializeEnemyComponent(Entity* enemy, float detectionRange, float attackRange, float movementSpeed, float attackDamage) {
    EnemyComponent* enemyComponent = (EnemyComponent*)calloc(1, sizeof(EnemyComponent));
    glm_vec3_zero(enemyComponent->direction);
    enemyComponent->detectionRange = detectionRange;
    enemyComponent->attackRange = attackRange;
    enemyComponent->movementSpeed = movementSpeed;
    enemyComponent->attackDamage = attackDamage;
    enemyComponent->isAttacking = false;
    enemyComponent->isAlive = true;
    addComponent(enemy, COMPONENT_ENEMY, enemyComponent);
}

void updateEnemy(Entity* enemy, Entity* player, Scene* scene, GameState* gameState, float deltaTime) {
    EnemyComponent* enemyComponent = (EnemyComponent*)getComponent(enemy, COMPONENT_ENEMY);
    Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
    Animator* enemyAnimator = (Animator*)getComponent(enemy, COMPONENT_ANIMATOR);

    if (!enemyComponent->isAlive) {
        enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemDyingAnimation");
        return;
    }

    vec3 playerPos;
    glm_vec3_copy(((Model*)getComponent(player, COMPONENT_RENDERABLE))->position, playerPos);

    vec3 enemyPos;
    glm_vec3_copy(enemyModel->position, enemyPos);

    glm_vec3_sub(playerPos, enemyPos, enemyComponent->direction);
    float enemyDist = glm_vec3_norm(enemyComponent->direction);
    glm_vec3_normalize(enemyComponent->direction);
    float rotTarget = 0.0f;
    if (enemyDist < enemyComponent->detectionRange) {
        float omega = acos(glm_dot((vec3){0, 0, 1}, enemyComponent->direction));
        if (enemyComponent->direction[0] < 0) {
            omega = -omega;
        }

        float currentAngleDeg = glm_deg(enemyModel->rotation[1]);
        float targetAngleDeg = glm_deg(omega);
        while (targetAngleDeg - currentAngleDeg > 180) {
            targetAngleDeg -= 360;
        }
        while (targetAngleDeg - currentAngleDeg < -180) {
            targetAngleDeg += 360;
        }
        rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);

        // Check if the player is attacking and in range
        PlayerComponent* playerComponent = (PlayerComponent*)getComponent(player, COMPONENT_PLAYER);
        if (playerComponent->isAttacking && enemyDist < playerComponent->attackRange) {
            // Check if the player's attack animation has just started
            Animator* playerAnimator = (Animator*)getComponent(player, COMPONENT_ANIMATOR);
            if (playerAnimator->playTime == 0.0f) {
                enemyComponent->health -= playerComponent->attackDamage;
                enemyAnimator->playTime = 0.0f;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemHitAnimation");

                // Check if the enemy is dead
                if (enemyComponent->health <= 0.0f) {
                    enemyComponent->isAlive = false;
                    enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemDyingAnimation");
                    enemyAnimator->playTime = 0.0f;
                    return;
                }
            }
        }

        if (enemyDist < enemyComponent->attackRange) {
            if (!enemyComponent->isAttacking) {
                enemyComponent->isAttacking = true;
                enemyAnimator->playTime = 0.0f;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemPunchAnimation");
            }
            if (enemyAnimator->playTime > enemyAnimator->currentAnimation->anim_dur - 10) {
                damagePlayer(gameState, enemyComponent->attackDamage);
                isDamageShown = true;
                printf("L'ennemi frappe\n");
                enemyAnimator->playTime = 0.0f;
                enemyComponent->isAttacking = false;
            }
        } else {
            enemyComponent->isAttacking = false;
            enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemWalkingAnimation");
            vec3 moveVector;
            glm_vec3_scale(enemyComponent->direction, enemyComponent->movementSpeed * deltaTime, moveVector);
            glm_vec3_add(enemyPos, moveVector, enemyModel->position);
        }
    } else {
        enemyComponent->isAttacking = false;
        enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemIdleAnimation");
    }

    enemyModel->rotation[1] = glm_rad(rotTarget);
}


Entity* create_golem(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
        golem->isRenderable = false;
        glm_vec3_copy((vec3){x,y,z}, golem->position);
        glm_vec3_copy((vec3){scale,scale,scale}, golem->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, golem);

        Animation* golemIdleAnimation = AnimationCreate("assets/models/Golem/Mutant Breathing Idle.dae", golem, "golemIdleAnimation");
        Animation* golemWalkingAnimation = AnimationCreate("assets/models/Golem/Mutant Walking.dae", golem, "golemWalkingAnimation");
        Animation* golemPunchAnimation = AnimationCreate("assets/models/Golem/Mutant Swiping.dae", golem, "golemPunchAnimation");
        Animation* golemHitAnimation = AnimationCreate("assets/models/Golem/Standing React Small From Left.dae", golem, "golemHitAnimation");
        Animation* golemDyingAnimation = AnimationCreate("assets/models/Golem/Mutant Dying.dae", golem, "golemDyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemWalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemPunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemHitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemDyingAnimation);

        Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);
    
            EnemyComponent* enemyComponent = (EnemyComponent*)calloc(1, sizeof(EnemyComponent));
    glm_vec3_zero(enemyComponent->direction);
    enemyComponent->detectionRange = 20.0f;
    enemyComponent->attackRange = 3.0f;
    enemyComponent->movementSpeed = 3.0f;
    enemyComponent->attackDamage = 10.0f;
    enemyComponent->isAttacking = false;
    enemyComponent->isAlive = true;
    enemyComponent->takeDamage = false;
    enemyComponent->health = 100.0f;
    addComponent(enemy, COMPONENT_ENEMY, enemyComponent);
    }
    return enemy;
}

Entity* create_golemBlue(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/GolemBleu/Mutant Breathing Idle.dae");
        golem->isRenderable = false;
        glm_vec3_copy((vec3){x,y,z}, golem->position);
        glm_vec3_copy((vec3){scale,scale,scale}, golem->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, golem);

        Animation* golemIdleAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Breathing Idle.dae", golem, "golemIdleAnimation");
        Animation* golemWalkingAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Walking.dae", golem, "golemWalkingAnimation");
        Animation* golemPunchAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Swiping.dae", golem, "golemPunchAnimation");
        Animation* golemHitAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Hit.dae", golem, "golemHitAnimation");
        Animation* golemDyingAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Dying.dae", golem, "golemDyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemWalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemPunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemHitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemDyingAnimation);

        Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);

    }
    return enemy;
}
Entity* create_golemPurple(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/GolemViolet/Mutant Breathing Idle.dae");
        golem->isRenderable = false;
        glm_vec3_copy((vec3){x,y,z}, golem->position);
        glm_vec3_copy((vec3){scale,scale,scale}, golem->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, golem);

        Animation* golemIdleAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Breathing Idle.dae", golem, "golemIdleAnimation");
        Animation* golemWalkingAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Walking copy.dae", golem, "golemWalkingAnimation");
        Animation* golemPunchAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Swiping.dae", golem, "golemPunchAnimation");
        Animation* golemHitAnimation = AnimationCreate("assets/models/GolemViolet/Standing React Small From Left.dae", golem, "golemHitAnimation");
        Animation* golemDyingAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Dying.dae", golem, "golemDyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemWalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemPunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemHitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemDyingAnimation);

        Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);
        EnemyComponent* enemyComponent = (EnemyComponent*)calloc(1, sizeof(EnemyComponent));
    glm_vec3_zero(enemyComponent->direction);
    enemyComponent->detectionRange = 20.0f;
    enemyComponent->attackRange = 3.0f;
    enemyComponent->movementSpeed = 3.0f;
    enemyComponent->attackDamage = 5.0f;
    enemyComponent->isAttacking = false;
    enemyComponent->isAlive = true;
    enemyComponent->health = 100.0f;
    addComponent(enemy, COMPONENT_ENEMY, enemyComponent);
    }
    return enemy;
}


void golemLogic(Scene* scene, GameState* gameState, Entity* golem, Entity* player) {
    // float rotTarget = 0.0f;
    // vec3 enemyDir;
    // Model* golemModel = (Model*)getComponent(golem, COMPONENT_RENDERABLE);
    // Model* playerModel = (Model*)getComponent(player, COMPONENT_RENDERABLE);
    // Collider* playerCollider = (Collider*)getComponent(player,COMPONENT_COLLIDER);
    // Animator* golemAnimator = (Animator*)getComponent(golem, COMPONENT_ANIMATOR);
    // glm_vec3_sub(playerModel->position, golemModel->position, enemyDir);
    // float enemyDist = glm_vec3_norm(enemyDir);
    // glm_vec3_normalize(enemyDir);
    // if (enemyDir[0]!=.0f || enemyDir[1]!=.0f || enemyDir[2]!=.0f) {
    //     float omega = acos(glm_dot((vec3){0, 0, 1}, enemyDir));
    //     if (enemyDir[0] < 0) {
    //         omega = -omega;
    //     }
    //     float currentAngleDeg = glm_deg(golemModel->rotation[1]);
    //     float targetAngleDeg = glm_deg(omega);
    //     while (targetAngleDeg - currentAngleDeg > 180) {
    //         targetAngleDeg -= 360;
    //     }
    //     while (targetAngleDeg - currentAngleDeg < -180) {
    //         targetAngleDeg += 360;
    //     }
    //     rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);
    // }
    // if (enemyDist < 2.0f) {
    //     if (!gameState->enemyIsAttacking) {
    //         gameState->enemyIsAttacking = true;
    //         golemAnimator->playTime = 0.0f;
    //         golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemPunchAnimation");
    //     }
    //     if (golemAnimator->playTime > golemAnimator->currentAnimation->anim_dur - 10) {
    //         gameState->playerHealth -= 10.0f;
    //         golemAnimator->playTime = 0.0f;
    //         gameState->enemyIsAttacking = false;
    //     }
    //     golemModel->rotation[1] = glm_rad(rotTarget);
    // } else if (enemyDist < 15.0f) {
    //         golemModel->rotation[1] = glm_rad(rotTarget);
    //         gameState->enemyIsAttacking = false;
    //         golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemWalkingAnimation");
    //         glm_vec3_scale(enemyDir, 2 * scene->deltaTime, enemyDir);
    //         glm_vec3_add(golemModel->position, enemyDir, golemModel->position);
    //     }
    //  else {
    //     gameState->enemyIsAttacking = false;
    //     golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemIdleAnimation");
    // }
}

Entity* create_gobelin(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* gobelin = (Model*)calloc(1, sizeof(Model));
        ModelCreate(gobelin, "assets/models/Gobelin/GobelinIdle.dae");
        glm_vec3_copy((vec3){x,y,z}, gobelin->position);
        glm_vec3_copy((vec3){scale,scale,scale}, gobelin->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, gobelin);

        Animation* gobelinIdleAnimation = AnimationCreate("assets/models/Gobelin/GobelinIdle.dae", gobelin, "gobelinIdleAnimation");
        Animation* gobelinDyingAnimation = AnimationCreate("assets/models/Gobelin/GobelinDying.dae", gobelin, "gobelinDyingAnimation");
        Animation* gobelinHittingAnimation = AnimationCreate("assets/models/Gobelin/GobelinHitting.dae", gobelin, "gobelinHittingAnimation");
        Animation* gobelinSpearAnimation = AnimationCreate("assets/models/Gobelin/GobelinSpear.dae", gobelin, "gobelinSpearAnimation");
        Animation* gobelinSwordAnimation = AnimationCreate("assets/models/Gobelin/GobelinSword.dae", gobelin, "gobelinSwordAnimation");
        Animation* gobelinWalkAnimation = AnimationCreate("assets/models/Gobelin/Mutant Walking.dae", gobelin, "gobelinWalkAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, gobelinIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, gobelinDyingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, gobelinHittingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, gobelinSpearAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, gobelinSwordAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, gobelinWalkAnimation);
        
        Animator* gobelinAnimator = AnimatorCreate(gobelinIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, gobelinAnimator);
    }
    return enemy;
}

Entity* create_skeleton(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* skeleton = (Model*)calloc(1, sizeof(Model));
        ModelCreate(skeleton, "assets/models/Skeleton/Breathing Idle.dae");
        glm_vec3_copy((vec3){x,y,z}, skeleton->position);
        glm_vec3_copy((vec3){scale,scale,scale}, skeleton->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, skeleton);

        Animation* skeletonIdleAnimation = AnimationCreate("assets/models/Skeleton/Breathing Idle.dae", skeleton, "skeletonIdleAnimation");
        Animation* skeletonDyingAnimation = AnimationCreate("assets/models/Skeleton/Dying.dae", skeleton, "skeletonDyingAnimation");
        Animation* skeletonHittingAnimation = AnimationCreate("assets/models/Skeleton/Standing React Large From Front.dae", skeleton, "skeletonHittingAnimation");
        Animation* skeletonSpearAnimation = AnimationCreate("assets/models/Skeleton/Bayonet Stab.dae", skeleton, "skeletonSpearAnimation");
        Animation* skeletonSwordAnimation = AnimationCreate("assets/models/Skeleton/Sword And Shield Slash.dae", skeleton, "skeletonSwordAnimation");
        Animation* skeletonWalkAnimation = AnimationCreate("assets/models/Skeleton/Sword And Shield Walk.dae", skeleton, "skeletonWalkAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, skeletonIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, skeletonDyingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, skeletonHittingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, skeletonSpearAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, skeletonSwordAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, skeletonWalkAnimation);
        
        Animator* skeletonAnimator = AnimatorCreate(skeletonIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, skeletonAnimator);
    }
    return enemy;
}