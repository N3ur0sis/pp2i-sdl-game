#include <Engine.h>
#include <Textures.h>
#include <Controls.h>
#include <Scene.h>
#include <System.h>



/* Global variable, only for things that won't change during the game or used for intitialization */

static const char* g_WindowTitle = "Game";


/* Entry point of the program */
int main(void){

    /* Create an instance of the application */
    Application* game = ApplicationCreate(g_WindowWidth, g_WindowHeight, g_WindowTitle);

    Scene scene;
    scene.numEntities = 0;
    /* Load and compile shaders */
    scene.shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    /* Create a scene camera */
    scene.camera = camera_create(28, 5, 10, g_WindowWidth, g_WindowHeight);
    glUniform3fv(scene.shader->m_locations.cameraPosition, 1, scene.camera->Position);
    /* Create a skybox */
    scene.skybox = SkyboxCreate();

    /* Enemy Entity */
    Entity* enemy = createEntity(&scene);
    if (enemy != NULL) {
        Model* golem = (Model*)calloc(1, sizeof(Model));
        ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
        addComponent(enemy, COMPONENT_RENDERABLE, golem);
        
        Animation* golemIdleAnimation = AnimationCreate("assets/models/Golem/Mutant Breathing Idle.dae", golem,"golemIdleAnimation");
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
    Entity* playerEntity = createEntity(&scene);
    Player* player;
    if (playerEntity != NULL) {
        player = playerCreate("assets/models/LoPotitChat/PlayerWalk.dae");
        Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerAttack.dae", player->playerModel, "playerAttackAnimation");
        Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerWalk.dae", player->playerModel, "playerWalkingAnimation");
        Animator* playerAnimator = AnimatorCreate(walkingAnimation);
        player->playerAnimator = playerAnimator;
        glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, player->playerModel->scale);
        glm_vec3_copy((vec3){28.0f, 0.1f, 7.0f}, player->velocity);
        
        addComponent(playerEntity, COMPONENT_RENDERABLE, player->playerModel);
        addComponent(playerEntity, COMPONENT_ANIMATION, attackAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATION, walkingAnimation);
        addComponent(playerEntity, COMPONENT_ANIMATOR, playerAnimator);
    }

    /* Sword Entity */
    Entity* swordEntity = createEntity(&scene);
    if (swordEntity != NULL) {
        Model* sword = (Model*)calloc(1, sizeof(Model));
        ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
        addComponent(swordEntity, COMPONENT_RENDERABLE, sword);
    // Adding attachment component to the sword entity
    AttachmentComponent* swordAttachment = (AttachmentComponent*)calloc(1, sizeof(AttachmentComponent));
    swordAttachment->boneIndex = 21; // Example bone index
    swordAttachment->parentAnimator = player->playerAnimator;
    swordAttachment->parentModel = player->playerModel;
    glm_vec3_copy((vec3){-1.3f, -0.7f, 0.3f}, swordAttachment->offsetPosition);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, swordAttachment->offsetRotation);
    glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, swordAttachment->offsetScale);
    addComponent(swordEntity, COMPONENT_ATTACHMENT, swordAttachment);
    }

    /* Map Entity */
    Entity* mapEntity = createEntity(&scene);
    if (mapEntity != NULL) {
        Model* map = (Model*)calloc(1, sizeof(Model));
        ModelCreate(map, "assets/models/start/start.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);
        
        Collider* mapCollision = ColliderCreate("assets/models/start/col.obj");
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -0.5f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Light Entity */
    Entity* lightEntity = createEntity(&scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene.shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Temp variables */
    bool enemyIsAttacking = false;
    bool playerIsAttacking = false;
    float playerHealth = 100.0f;

    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    while (game->running) {
        StartFrame(game);
        Uint32 currentTime = SDL_GetTicks();
        scene.deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        /* Game Logic */
        float rotTarget = 0.0f;
        vec3 enemyDir;
        glm_vec3_sub(player->playerModel->position, ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->position, enemyDir);
        float enemyDist = glm_vec3_norm(enemyDir);
        glm_vec3_normalize(enemyDir);
        if (enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f) {
            float omega = acos(glm_dot((vec3){0, 0, 1}, enemyDir));
            if (enemyDir[0] < 0) {
                omega = -omega;
            }
            if (getMouseButtonState(1) && !playerIsAttacking) {
                playerIsAttacking = true;
                player->playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation");
                player->playerAnimator->playTime = 0.0f;
            } else if (!playerIsAttacking) {
                player->playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerWalkingAnimation");
            }
            if (player->playerAnimator->playTime > player->playerAnimator->currentAnimation->anim_dur - 10 && playerIsAttacking) {
                playerIsAttacking = false;
                player->playerAnimator->playTime = 0.0f;
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
            if (!enemyIsAttacking) {
                enemyIsAttacking = true;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime = 0.0f;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemPunchAnimation");
            }
            if (((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime > ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation->anim_dur - 10) {
                playerHealth -= 10.0f;
                ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->playTime = 0.0f;
                enemyIsAttacking = false;
            }
            ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->rotation[1] = glm_rad(rotTarget);
        } else if (enemyDist < 15.0f) {
            ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->rotation[1] = glm_rad(rotTarget);
            enemyIsAttacking = false;
            ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemWalkingAnimation");
            glm_vec3_scale(enemyDir, 2 * scene.deltaTime, enemyDir);
            glm_vec3_add(((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->position, enemyDir, ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->position);
        } else {
            enemyIsAttacking = false;
            ((Animator*)getComponent(enemy, COMPONENT_ANIMATOR))->currentAnimation = (Animation*)getAnimationComponent(enemy, "golemIdleAnimation");
        }

        if(!((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || player->playerAnimator->currentAnimation == (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation"))){
            player->playerAnimator->playTime = 0.0f;
        }
        playerMovement(player, scene.deltaTime, scene.camera, (Model*)getComponent(enemy, COMPONENT_RENDERABLE));
        cameraControl(scene.camera);


    /* Physics Update */

        for (int i = 0; i < ((Collider*)getComponent(mapEntity, COMPONENT_COLLIDER))->numCollider; i++) {
            mat4 id;
            glm_translate_make(id, (vec3){0.0f, -0.5f, 0.0f});
            glm_aabb_transform(((Collider*)getComponent(mapEntity, COMPONENT_COLLIDER))->boundingBoxReference[i], id, ((Collider*)getComponent(mapEntity, COMPONENT_COLLIDER))->boundingBox[i]);
            if (glm_aabb_aabb(player->collider->boundingBox[0], ((Collider*)getComponent(mapEntity, COMPONENT_COLLIDER))->boundingBox[i])) {
                printf("collision with %d\n", i);
                glm_vec3_copy(player->playerModel->position, player->velocity);
            }
        }
        glm_vec3_copy(player->velocity, player->playerModel->position);




        renderSystem(&scene);

        EndFrame(game);
    }

    /* Clean every resource allocated */
    ModelFree(player->playerModel);
    ModelFree((Model*)getComponent(mapEntity, COMPONENT_RENDERABLE));
    free(scene.camera);
    DeleteShaders(scene.shader);
    SkyboxDelete(scene.skybox);
    WindowDelete(game->window);
    EngineQuit();
}
