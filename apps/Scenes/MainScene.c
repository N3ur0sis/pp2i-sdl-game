#include <MainScene.h>


bool is_tabingMain = false;



void startMainScene(Scene* scene, GameState* gameState) {
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    UseShaders(scene->shader);
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");
    /* Create a scene camera */
    scene->camera = camera_create(28, 5, 10, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    Entity* playerEntity = create_player(scene,28.0f,0.1f,7.0f);

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
        ModelCreate(map, "assets/models/main/main.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        // Collider* mapCollision = ColliderCreate("assets/models/start/col.obj");
        // glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -1.0f, 0.0f});
        // UpdateCollider(mapCollision);
        // addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f, 0.1f, 500.0f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }
}



void updateMainScene(Scene* scene, GameState* gameState) {
    
    Entity* playerEntity = &scene->entities[0];
    Entity* swordEntity = &scene->entities[1];
    Inventory* inventory = &gameState->inventory;
    bool* isBusy = &((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy;
    checkDead(gameState);
    if (gameState->isPlayerDead) {
        *isBusy = true;
        if (!gameState->restarting){
            RenderText("Vous êtes mort", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            RenderText("Appuyez sur r pour recommencer", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2 - 50, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        }
        if (getKeyState(SDLK_r)) {
            *isBusy = false;
            ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            gameState->playerHealth = 100.0f;
            gameState->isPlayerDead = false;
            gameState->change = true;
            gameState->nextSceneIndex = 3;
            gameState->previousSceneIndex = 3;
            gameState->restarting = false;
            setKeyState(SDLK_r, 0);
        }
    }

    if (playerEntity) {
        Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
        Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
        RigidBody* playerRigidbody = (RigidBody*)getComponent(playerEntity, COMPONENT_RIGIDBODY);


        // if (getKeyState(TAB) && !is_tabingMain) {
        //     is_tabingMain = true;
        //     if (inventory->isOpened) {
        //         inventory->isOpened = false;
        //         *isBusy = false;
        //     } else {
        //         inventory->isOpened = true;
        //         *isBusy = true;
        //     }
        // } else if (!getKeyState(TAB)) {
        //     is_tabingMain = false;
        // }

        // if (inventory->isOpened) {
        //     InventoryPrint(inventory, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        // }
        playerMovement(playerEntity, scene->deltaTime, scene->camera, NULL);
    }   
}



void unloadMainScene(Scene* scene){
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