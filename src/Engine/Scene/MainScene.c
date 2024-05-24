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

    Entity* playerEntity = create_player(scene,-145.0f,9.1f,94.0f);
    
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

    /*City Part*/
    Entity* city = createEntity(scene);
    if (city != NULL) {
        Model* cityModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(cityModel, "assets/models/main/city.obj");
        addComponent(city, COMPONENT_RENDERABLE, cityModel);
        compute_center_of_volume(cityModel);
        cityModel->isRenderable = false;
    }

    Entity* debut = createEntity(scene);
    if (debut != NULL) {
        Model* debutModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(debutModel, "assets/models/main/debut.obj");
        addComponent(debut, COMPONENT_RENDERABLE, debutModel);
        compute_center_of_volume(debutModel);
        debutModel->isRenderable = false;
    }
    
    Entity* foret1 = createEntity(scene);
    if (foret1 != NULL) {
        Model* foret1Model = (Model*)calloc(1, sizeof(Model));
        ModelCreate(foret1Model, "assets/models/main/foret1.obj");
        addComponent(foret1, COMPONENT_RENDERABLE, foret1Model);
        foret1Model->isRenderable = false;
    }

    Entity* foret2 = createEntity(scene);
    if (foret2 != NULL) {
        Model* foret2Model = (Model*)calloc(1, sizeof(Model));
        ModelCreate(foret2Model, "assets/models/main/foret2.obj");
        addComponent(foret2, COMPONENT_RENDERABLE, foret2Model);
        foret2Model->isRenderable = false;
    }

    Entity* foret3 = createEntity(scene);
    if (foret3 != NULL) {
        Model* foret3Model = (Model*)calloc(1, sizeof(Model));
        ModelCreate(foret3Model, "assets/models/main/foret3.obj");
        addComponent(foret3, COMPONENT_RENDERABLE, foret3Model);
        foret3Model->isRenderable = false;
    }

    Entity* lake = createEntity(scene);
    if (lake != NULL) {
        Model* lakeModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(lakeModel, "assets/models/main/lake.obj");
        addComponent(lake, COMPONENT_RENDERABLE, lakeModel);
        lakeModel->isRenderable = false;
    }

    Entity* main = createEntity(scene);
    if (main != NULL) {
        Model* mainModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(mainModel, "assets/models/main/main.obj");
        addComponent(main, COMPONENT_RENDERABLE, mainModel);
        mainModel->isRenderable = false;
    }

    Entity* mid = createEntity(scene);
    if (mid != NULL) {
        Model* midModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(midModel, "assets/models/main/mid.obj");
        addComponent(mid, COMPONENT_RENDERABLE, midModel);
        midModel->isRenderable = false;
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
    Model* playerModel = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE));
        if (getKeyState(SDLK_p)){
        printf("Le joueur est en %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    for (int i = 2;i<110;i++){
        Entity* map = &scene->entities[i];
        Model* mapModel = ((Model*)getComponent(map, COMPONENT_RENDERABLE));
        vec3 mapDir;
        glm_vec3_sub(playerModel->position,mapModel->center,mapDir);
        if (mapModel->isRenderable && glm_vec3_norm(mapDir)>=150.0f){
            mapModel->isRenderable = false;
        }
        else if(!mapModel->isRenderable && glm_vec3_norm(mapDir)<150.0f){
            mapModel->isRenderable = true;
        }
    }

    Entity* swordEntity = &scene->entities[1];
    Inventory* inventory = &gameState->inventory;
    bool* isBusy = &((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy;
    checkDead(gameState);
    if (gameState->isPlayerDead) {
        *isBusy = true;
        RenderText("Vous êtes mort", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("Appuyez sur r pour recommencer", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2 - 50, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getKeyState(SDLK_r)) {
            *isBusy = false;
            ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            gameState->playerHealth = 100.0f;
            gameState->isPlayerDead = false;
            gameState->change = true;
            gameState->nextSceneIndex = 3;
            gameState->previousSceneIndex = 3;
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