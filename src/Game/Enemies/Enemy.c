#include "Enemy.h"



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
        enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemDeathAnimation");
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

        if (enemyDist < enemyComponent->attackRange) {
            if (!enemyComponent->isAttacking) {
                enemyComponent->isAttacking = true;
                enemyAnimator->playTime = 0.0f;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemPunchAnimation");
            }
            if (enemyAnimator->playTime > enemyAnimator->currentAnimation->anim_dur - 10) {
                damagePlayer(gameState, enemyComponent->attackDamage);
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
        Animation* golemPunchAnimation = AnimationCreate("assets/models/Golem/Mutant Punch.dae", golem, "golemPunchAnimation");
        Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemIdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemWalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, golemPunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);
        
        Health* enemyHealth = (Health*)calloc(1, sizeof(Health));
        enemyHealth->health = 100.0f;
        enemyHealth->maxHealth = 100.0f;
        enemyHealth->isAlive = true;
        addComponent(enemy, COMPONENT_HEALTH, enemyHealth);
            EnemyComponent* enemyComponent = (EnemyComponent*)calloc(1, sizeof(EnemyComponent));
    glm_vec3_zero(enemyComponent->direction);
    enemyComponent->detectionRange = 20.0f;
    enemyComponent->attackRange = 3.0f;
    enemyComponent->movementSpeed = 3.0f;
    enemyComponent->attackDamage = 10.0f;
    enemyComponent->isAttacking = false;
    enemyComponent->isAlive = true;
    addComponent(enemy, COMPONENT_ENEMY, enemyComponent);
    }
    return enemy;
}

void golemLogic(Scene* scene, GameState* gameState, Entity* golem, Entity* player) {
    float rotTarget = 0.0f;
    vec3 enemyDir;
    Model* golemModel = (Model*)getComponent(golem, COMPONENT_RENDERABLE);
    Model* playerModel = (Model*)getComponent(player, COMPONENT_RENDERABLE);
    Collider* playerCollider = (Collider*)getComponent(player,COMPONENT_COLLIDER);
    Animator* golemAnimator = (Animator*)getComponent(golem, COMPONENT_ANIMATOR);
    Health* health = (Health*)getComponent(golem, COMPONENT_HEALTH);
    if (health->health <= 0.0f) {
        golemModel->isRenderable = false;
        health->isAlive = false;
        return;
    }
    glm_vec3_sub(playerModel->position, golemModel->position, enemyDir);
    float enemyDist = glm_vec3_norm(enemyDir);
    glm_vec3_normalize(enemyDir);
    if (enemyDir[0]!=.0f || enemyDir[1]!=.0f || enemyDir[2]!=.0f) {
        float omega = acos(glm_dot((vec3){0, 0, 1}, enemyDir));
        if (enemyDir[0] < 0) {
            omega = -omega;
        }
        float currentAngleDeg = glm_deg(golemModel->rotation[1]);
        float targetAngleDeg = glm_deg(omega);
        while (targetAngleDeg - currentAngleDeg > 180) {
            targetAngleDeg -= 360;
        }
        while (targetAngleDeg - currentAngleDeg < -180) {
            targetAngleDeg += 360;
        }
        rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);
    }
    if (enemyDist < 2.0f) {
        if (!gameState->enemyIsAttacking) {
            gameState->enemyIsAttacking = true;
            golemAnimator->playTime = 0.0f;
            golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemPunchAnimation");
        }
        if (golemAnimator->playTime > golemAnimator->currentAnimation->anim_dur - 10) {
            gameState->playerHealth -= 10.0f;
            golemAnimator->playTime = 0.0f;
            gameState->enemyIsAttacking = false;
        }
        golemModel->rotation[1] = glm_rad(rotTarget);
    } else if (enemyDist < 15.0f) {
            golemModel->rotation[1] = glm_rad(rotTarget);
            gameState->enemyIsAttacking = false;
            golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemWalkingAnimation");
            glm_vec3_scale(enemyDir, 2 * scene->deltaTime, enemyDir);
            glm_vec3_add(golemModel->position, enemyDir, golemModel->position);
        }
     else {
        gameState->enemyIsAttacking = false;
        golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemIdleAnimation");
    }
}
