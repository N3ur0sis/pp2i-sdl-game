#include "Ennemy.h"


Entity* create_golem(Scene* scene){
    Entity* enemy = createEntity(scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
        addComponent(enemy, COMPONENT_RENDERABLE, golem);
        golem->isRenderable = false;
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
    return enemy;
}

Entity* golemLogic(Scene* scene,GameState* gameState,Entity* golem,Entity* player){
    float rotTarget = 0.0f;
    vec3 enemyDir;
    Model* golemModel = ((Model*)getComponent(golem, COMPONENT_RENDERABLE));
    Model* playerModel = ((Model*)getComponent(player, COMPONENT_RENDERABLE));
    Animator* golemAnimator =  ((Animator*)getComponent(golem, COMPONENT_ANIMATOR));
    
    glm_vec3_sub(playerModel->position, golemModel->position, enemyDir);
    float enemyDist = glm_vec3_norm(enemyDir);
    glm_vec3_normalize(enemyDir);
    if (enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f) {
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
    if (enemyDist < 3.0f) {
        if (!gameState->enemyIsAttacking) {
            gameState->enemyIsAttacking = true;
            golemAnimator->playTime = 0.0f;
            golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemPunchAnimation");
        }
        if (golemAnimator->playTime >golemAnimator->currentAnimation->anim_dur - 10) {
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
    } else {
        gameState->enemyIsAttacking = false;
        golemAnimator->currentAnimation = (Animation*)getAnimationComponent(golem, "golemIdleAnimation");
    }
}