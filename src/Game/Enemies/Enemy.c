#include "Enemy.h"

bool isDamageShown = false;
bool damageSent = false;
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
        enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "DyingAnimation");
        if(enemyAnimator->playTime>=3000.f){
            enemyModel->isRenderable = false;
            // gameState->money += 35;
        }
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
        Animator* playerAnimator = (Animator*)getComponent(player, COMPONENT_ANIMATOR);
        if (playerComponent->isAttacking && enemyDist < playerComponent->attackRange) {
            printf("player is in range\n");
            enemyComponent->health -= playerComponent->attackDamage;
            // Trigger enemy hit animation in the middle of the player's attack animation
            // if (playerAnimator->playTime >= playerAnimator->currentAnimation->anim_dur / 4 &&
            //     playerAnimator->playTime < playerAnimator->currentAnimation->anim_dur / 4 + deltaTime) {
            //     enemyComponent->health -= playerComponent->attackDamage;
            //     enemyAnimator->playTime = 0.0f;
            //     printf("%f\n", enemyComponent->health);
            //     enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemHitAnimation");
            //     printf("%f\n", enemyComponent->health);
            //     // Check if the enemy is dead
            if (enemyComponent->health <= 0.0f) {
                enemyComponent->isAlive = false;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "DyingAnimation");
                enemyAnimator->playTime = 0.0f;
                return;
            }
        }
        // printf("%f\n", enemyComponent->attackCooldown);
        if (enemyDist < enemyComponent->attackRange) {
            // Implement attack cooldown
            if (!enemyComponent->isAttacking) {
                if(enemyComponent->attackCooldown == 0.0f){

                enemyComponent->isAttacking = true;
                enemyAnimator->playTime = 0.0f;
                damageSent = false;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "PunchAnimation");
                // Set a cooldown timer
                enemyComponent->attackCooldown = ((Animation*)getAnimationComponent(enemy, "PunchAnimation"))->anim_dur / 1000  + 3.0f;  // Set cooldown duration here
                }
            }
            if (enemyAnimator->playTime > ((Animation*)getAnimationComponent(enemy, "PunchAnimation"))->anim_dur / 2 && !damageSent) {
                damagePlayer(gameState, enemyComponent->attackDamage);
                isDamageShown = true;
                damageSent = true;
            }
            if (enemyComponent->attackCooldown < 1) {
                enemyComponent->isAttacking = false;
                enemyAnimator->playTime = 0.0f;
                enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "IdleAnimation");

            }
        } else {
            enemyComponent->isAttacking = false;
            enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "WalkingAnimation");
            vec3 moveVector;
            glm_vec3_scale(enemyComponent->direction, enemyComponent->movementSpeed * deltaTime, moveVector);
            glm_vec3_add(enemyPos, moveVector, enemyModel->position);
        }
    } else {
        enemyComponent->isAttacking = false;
        enemyAnimator->currentAnimation = (Animation*)getAnimationComponent(enemy, "IdleAnimation");
    }

    // Decrement attack cooldown
    if (enemyComponent->attackCooldown > 0.0f) {
        enemyComponent->attackCooldown -= deltaTime;
        if (enemyComponent->attackCooldown < 0.0f) {
            enemyComponent->attackCooldown = 0.0f;
        }
    }

    // Decrement attack cooldown
    if (enemyComponent->attackCooldown > 0.0f) {
        enemyComponent->attackCooldown -= deltaTime;
        if (enemyComponent->attackCooldown < 0.0f) {
            enemyComponent->attackCooldown = 0.0f;
        }
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

        Animation* IdleAnimation = AnimationCreate("assets/models/Golem/Mutant Breathing Idle.dae", golem, "IdleAnimation");
        Animation* WalkingAnimation = AnimationCreate("assets/models/Golem/Mutant Walking.dae", golem, "WalkingAnimation");
        Animation* PunchAnimation = AnimationCreate("assets/models/Golem/Mutant Swiping.dae", golem, "PunchAnimation");
        Animation* HitAnimation = AnimationCreate("assets/models/Golem/Standing React Small From Left.dae", golem, "HitAnimation");
        Animation* DyingAnimation = AnimationCreate("assets/models/Golem/Mutant Dying.dae", golem, "DyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, WalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, PunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, HitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, DyingAnimation);

        Animator* golemAnimator = AnimatorCreate(IdleAnimation);
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

        Animation* IdleAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Breathing Idle.dae", golem, "IdleAnimation");
        Animation* WalkingAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Walking copy.dae", golem, "WalkingAnimation");
        Animation* PunchAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Swiping.dae", golem, "PunchAnimation");
        Animation* HitAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Hit.dae", golem, "HitAnimation");
        Animation* DyingAnimation = AnimationCreate("assets/models/GolemBleu/Mutant Dying.dae", golem, "DyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, WalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, PunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, HitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, DyingAnimation);

        Animator* golemAnimator = AnimatorCreate(IdleAnimation);
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
Entity* create_golemPurple(Scene* scene,float x,float y,float z,float scale){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/GolemViolet/Mutant Breathing Idle.dae");
        golem->isRenderable = false;
        glm_vec3_copy((vec3){x,y,z}, golem->position);
        glm_vec3_copy((vec3){scale,scale,scale}, golem->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, golem);

        Animation* IdleAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Breathing Idle.dae", golem, "IdleAnimation");
        Animation* WalkingAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Walking copy.dae", golem, "WalkingAnimation");
        Animation* PunchAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Swiping.dae", golem, "PunchAnimation");
        Animation* HitAnimation = AnimationCreate("assets/models/GolemViolet/Standing React Small From Left.dae", golem, "HitAnimation");
        Animation* DyingAnimation = AnimationCreate("assets/models/GolemViolet/Mutant Dying.dae", golem, "DyingAnimation");
        
        addComponent(enemy, COMPONENT_ANIMATION, IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, WalkingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, PunchAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, HitAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, DyingAnimation);

        Animator* golemAnimator = AnimatorCreate(IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, golemAnimator);
        EnemyComponent* enemyComponent = (EnemyComponent*)calloc(1, sizeof(EnemyComponent));
    glm_vec3_zero(enemyComponent->direction);
    enemyComponent->detectionRange = 20.0f;
    enemyComponent->attackRange = 3.0f;
    enemyComponent->movementSpeed = 3.0f;
    enemyComponent->attackDamage = 5.0f;
    enemyComponent->isAttacking = false;
    enemyComponent->isAlive = true;
    enemyComponent->health = 10.0f;
    addComponent(enemy, COMPONENT_ENEMY, enemyComponent);
    }
    return enemy;
}

Entity* create_skeleton(Scene* scene, float x, float y, float z, float scale) {
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* skeleton = (Model*)calloc(1, sizeof(Model));
        ModelCreate(skeleton, "assets/models/Skeleton/Breathing Idle.dae");
        skeleton->isRenderable = false; // Set initial visibility
        glm_vec3_copy((vec3){x, y, z}, skeleton->position);
        glm_vec3_copy((vec3){scale, scale, scale}, skeleton->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, skeleton);

         Animation* IdleAnimation = AnimationCreate("assets/models/Skeleton/Breathing Idle.dae", skeleton, "IdleAnimation");
         Animation* DyingAnimation = AnimationCreate("assets/models/Skeleton/Dying.dae", skeleton, "DyingAnimation");
         Animation* HitAnimation = AnimationCreate("assets/models/Skeleton/Standing React Large From Front.dae", skeleton, "HitAnimation");
         //Animation* SpearAnimation = AnimationCreate("assets/models/Skeleton/Bayonet Stab.dae", skeleton, "SpearAnimation"); censé ne pas etre commenté
         Animation* PunchAnimation = AnimationCreate("assets/models/Skeleton/Sword And Shield Slash.dae", skeleton, "PunchAnimation"); //censé etre swordanimation
         Animation* WalkingAnimation = AnimationCreate("assets/models/Skeleton/Sword And Shield Walk.dae", skeleton, "WalkingAnimation");

        addComponent(enemy, COMPONENT_ANIMATION, IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, DyingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, HitAnimation);
        //addComponent(enemy, COMPONENT_ANIMATION, SpearAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, PunchAnimation); //censé etre swordanimation
        addComponent(enemy, COMPONENT_ANIMATION, WalkingAnimation);

        Animator* skeletonAnimator = AnimatorCreate(IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, skeletonAnimator);

        // Adding EnemyComponent
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


Entity* create_gobelin(Scene* scene, float x, float y, float z, float scale) {
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* gobelin = (Model*)calloc(1, sizeof(Model));
        ModelCreate(gobelin, "assets/models/Gobelin/GobelinIdle.dae");
        gobelin->isRenderable = false; // Set initial visibility
        glm_vec3_copy((vec3){x, y, z}, gobelin->position);
        glm_vec3_copy((vec3){scale, scale, scale}, gobelin->scale);
        addComponent(enemy, COMPONENT_RENDERABLE, gobelin);

        Animation* IdleAnimation = AnimationCreate("assets/models/Gobelin/GobelinIdle.dae", gobelin, "IdleAnimation");
        Animation* DyingAnimation = AnimationCreate("assets/models/Gobelin/GobelinDying.dae", gobelin, "DyingAnimation");
        Animation* HitAnimation = AnimationCreate("assets/models/Gobelin/GobelinHitting.dae", gobelin, "HitAnimation");
        //Animation* SpearAnimation = AnimationCreate("assets/models/Gobelin/GobelinSpear.dae", gobelin, "SpearAnimation");
        Animation* PunchAnimation = AnimationCreate("assets/models/Gobelin/GobelinSword.dae", gobelin, "PunchAnimation"); //SwordAnimation
        Animation* WalkingAnimation = AnimationCreate("assets/models/Gobelin/Mutant Walking.dae", gobelin, "WalkingAnimation");

        addComponent(enemy, COMPONENT_ANIMATION, IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, DyingAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, HitAnimation);
        //addComponent(enemy, COMPONENT_ANIMATION, SpearAnimation);
        addComponent(enemy, COMPONENT_ANIMATION, PunchAnimation); //censé etre swordanimation
        addComponent(enemy, COMPONENT_ANIMATION, WalkingAnimation);

        Animator* gobelinAnimator = AnimatorCreate(IdleAnimation);
        addComponent(enemy, COMPONENT_ANIMATOR, gobelinAnimator);

        // Adding EnemyComponent
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