#include <StartScene.h>

// Define an enum for different checkpoints
typedef enum {
    CHECKPOINT_START,
    CHECKPOINT_SWORD,
    CHECKPOINT_ENEMY,
    CHECKPOINT_END
} Checkpoint;

Checkpoint currentCheckpoint = CHECKPOINT_START;


bool checkpoint_sword;
bool is_clicking = false;
bool is_tabingStart = false;
bool isBarrierDestroyed;
int click_counter = 0 ;
Inventory* inventory;
Inventory* marchantInventory;
Uint32 timeOfHit;
const Uint32 enemyHitTextDisplayDuration = 750; // ms

void startStartScene(Scene* scene, GameState* gameState) {
    checkpoint_sword = false;
    isBarrierDestroyed = false;
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    UseShaders(scene->shader);
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");

    /* Create a scene camera */
    scene->camera = camera_create(20, 22, -30, gameState->g_WindowWidth, gameState->g_WindowHeight);
    
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    /* Enemy Entity */
    Entity* golem = create_golemPurple(scene,0.0f,0.1f,0.0f,0.5f);

    /* Player Entity */
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
        ModelCreate(map, "assets/models/start/start.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        Collider* mapCollision = ColliderCreate("assets/models/start/col.obj");
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -9.0f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f, 0.1f, 500.0f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Chest Entity */
    Entity* chestEntity = createEntity(scene);
    if (chestEntity != NULL) {
        Model* chestClose = (Model*)calloc(1, sizeof(Model));
        ModelCreate(chestClose, "assets/models/Objet/Chest/ChestFerme.obj");
        glm_vec3_copy((vec3){-0.2f,1.2f,-33.3f},chestClose->position);
        addComponent(chestEntity, COMPONENT_RENDERABLE, chestClose);
        Collider* chestCollision = ColliderCreate("assets/models/Objet/Chest/ChestOuvert.obj");
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
        Collider* chestCollision = ColliderCreate("assets/models/Objet/Chest/ChestOuvert.obj");
        glm_translate_make(chestCollision->transformMatrix, (vec3){-0.2f, 1.2f, -33.3f});
        UpdateCollider(chestCollision);
        addComponent(chestOpenEntity, COMPONENT_COLLIDER, chestCollision);
    }
    Entity* startBarrierEntity = createEntity(scene);
    if (startBarrierEntity != NULL) {
        Model* startBarrier = (Model*)calloc(1, sizeof(Model));
        ModelCreate(startBarrier, "assets/models/Objet/StartBarrier/StartBarrier.obj");
        startBarrier->isRenderable = true;
        addComponent(startBarrierEntity, COMPONENT_RENDERABLE, startBarrier);

        ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->position[0] = -40.0f;
        ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->position[1] = 0.0f;
        ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->position[2] = -14.0f;

        Collider* startBarrierCollision = ColliderCreate("assets/models/Objet/StartBarrier/StartBarrier.obj");
        glm_translate_make(startBarrierCollision->transformMatrix, (vec3){-40.0f, 0.0f, -14.0f});
        UpdateCollider(startBarrierCollision);
        addComponent(startBarrierEntity, COMPONENT_COLLIDER, startBarrierCollision);

    }

    Entity* Marchand = createMarchand(scene, (vec3){-15.0f,0.1f,-10.0f}, (vec3){2.0f, 2.0f, 2.0f}, (vec3){0.0f, 3.14f, 0.0f});
    marchantInventory = gameState->marchantInventory;
    InventoryAddObjects(10, marchantInventory, Object_createFromId(1));
    InventoryAddObjects(1, marchantInventory, Object_createFromId(3));
    InventoryAddObjects(1, marchantInventory, Object_createFromId(4));

    
    inventory = gameState->inventory;
    InventoryAddObjects(2, inventory, Object_createFromId(1));
    InventoryAddObjects(1, inventory, Object_createFromId(2));

    /* Create a scene camera */
    scene->camera = camera_create(0, 100, -100, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);


    /* Create a skybox */
    scene->skybox = SkyboxCreate();

}
 
void updateStartScene(Scene* scene, GameState* gameState) {
    Entity* enemy = &scene->entities[0];
    Entity* playerEntity = &scene->entities[1];
    Entity* swordEntity = &scene->entities[2];
    Entity* chestEntity = &scene->entities[5];
    Entity* chestOpenEntity = &scene->entities[6];
    Entity* startBarrierEntity = &scene->entities[7];


    Uint32 currentTime = SDL_GetTicks();
    bool* isBusy = &((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->isBusy;
    float x = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[0];
    float y = ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->position[2];
    checkDead(gameState);

    if(isDamageShown){
        isDamageShown = false;
        timeOfHit = SDL_GetTicks();
        }

    if(SDL_GetTicks() - timeOfHit < enemyHitTextDisplayDuration){
        RenderText("-10", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 45 + 140, 13 * gameState->g_WindowHeight / 15 + 20, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        
    }


    if (gameState->isPlayerDead) {
        *isBusy = true;
        if (!gameState->restarting) {
            RenderText("Vous êtes mort", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            RenderText("Appuyez sur r pour recommencer", (SDL_Color){255, 0, 0, 0}, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2 - 50, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        }
        if (getKeyState(SDLK_r)) {
            *isBusy = false;
            checkpoint_sword = false;
            is_clicking = false;
            isBarrierDestroyed = false;
            click_counter = 0 ;
            is_tabingStart = false;
            ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            ((Model*)getComponent(chestEntity, COMPONENT_RENDERABLE))->isRenderable = true;
            ((Model*)getComponent(chestOpenEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->isRenderable = true;
            ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            ((Model*)getComponent(chestEntity, COMPONENT_RENDERABLE))->isRenderable = true;
            ((Model*)getComponent(chestOpenEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->isRenderable = true;
            ((Model*)getComponent(enemy, COMPONENT_RENDERABLE))->isRenderable = false;
            float max_health = gameState->max_health;
            gameState->playerHealth = max_health;
            gameState->isPlayerDead = false;
            ChangeSceneEvent(gameState->nextSceneIndex);
            gameState->nextSceneIndex = 0;
            gameState->previousSceneIndex = 0;
            gameState->restarting = false;
            setKeyState(SDLK_r, 0);
        }
    }

        drawHUD(scene, gameState);
        Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
        Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
        RigidBody* playerRigidbody = (RigidBody*)getComponent(playerEntity, COMPONENT_RIGIDBODY);
        Model* enemyModel = (Model*)getComponent(enemy, COMPONENT_RENDERABLE);
        PlayerComponent* playerComponent = (PlayerComponent*)getComponent(playerEntity, COMPONENT_PLAYER);


        /* Game Logic */

        if (getKeyState(TAB) && !is_tabingStart) {
            is_tabingStart = true;
            if (inventory->isOpened) {
                inventory->isOpened = false;
                *isBusy = false;
            } else {
                inventory->isOpened = true;
                *isBusy = true;
            }
        } else if (!getKeyState(TAB)) {
            is_tabingStart = false;
        }
        if (inventory->isOpened) {
            InventoryPrint(inventory, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program, 0, 0);
        }
        
        updatePlayerAnimator(playerEntity,gameState);
        if (!*isBusy) {
            playerMovement(playerEntity, scene->deltaTime, scene->camera);
        }

            

        if(checkpoint_sword){

            updateEnemy(enemy,playerEntity,scene,gameState,scene->deltaTime);

        }
        

        if (x < -37.25 && y <-13.85 && y > -17.5 && !isBarrierDestroyed) {
            if (getMouseButtonState(1)) {
                ((Model*)getComponent(startBarrierEntity, COMPONENT_RENDERABLE))->isRenderable = false;
                glm_translate_make(((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->transformMatrix, (vec3){1000.0f, 1000.0f, 1000.0f});
                for(int k = 0; k < ((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->numCollider; k++){
                    glm_aabb_transform(((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->boundingBoxReference[k],((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->transformMatrix,((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->boundingBox[k]);
                }
                // glm_aabb_transform(((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->boundingBoxReference[0],((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->transformMatrix,((Collider*)getComponent(startBarrierEntity, COMPONENT_COLLIDER))->boundingBox[0]);
                isBarrierDestroyed = true;
            }
        }


        if (y < -29.25f) {
            ((RigidBody*)getComponent(playerEntity, COMPONENT_RIGIDBODY))->velocity[1] = 1.1f;
        } else {
            ((RigidBody*)getComponent(playerEntity, COMPONENT_RIGIDBODY))->velocity[1] = 0.1f;
        }
        

        SDL_Color color_black = {0, 0, 0, 0};
        SDL_Color color_white = {255, 255, 255, 0};
        if ((x < 8.0f) && x > 3.5f && (y < 10.0f) && y > 5.5f && !*isBusy) {            
            RenderText("Appuyer sur E pour interagir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            if (getKeyState(SDLK_e)) {
                *isBusy = true;     
                // ((Model*)getComponent(playerEntity, COMPONENT_RENDERABLE))->*isBusy = true;
            }
        } else if ((x < 8.0f) && x > 3.5f && (y < 10.0f) && y > 5.5f && *isBusy) {
            switch (click_counter) {
                case 0:
                    RenderText("Panneau étrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Bienvenue sur l'Île Oubliée, voyageur.", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Les secrets de cette terre ancienne   ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter++;
                        is_clicking = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
                    break;
                case 1:
                    RenderText("Panneau étrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("attendent ceux qui osent les découvrir.", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Explore les environs pour avancer.     ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter++;
                        is_clicking = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
                    break;
                case 2:
                    RenderText("Panneau étrange", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Chaque découverte est une clé.          ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Bonne chance dans ton aventure.         ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter = 0;
                        *isBusy = false;
                        is_clicking = true;

                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
            }
            playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerIdleAnimation");
        }

        if(y < -30.5f && y > -35.5f && x < 2.08f && x > -2.8 && !*isBusy && !checkpoint_sword){
            RenderText("Appuyer sur E pour interagir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            if (getKeyState(SDLK_e)) {
                *isBusy = true;     
                glm_vec3_copy((vec3){-7.72,4.02,-37.04}, scene->camera->Position);
                scene->camera->Yaw = 40.0f;
                scene->camera->Pitch = -20.0f;
            }
        }else if (y < -30.5f && y > -35.5f && x < 2.08f && x > -2.8 && *isBusy && !checkpoint_sword) {
            ((Model*)getComponent(chestEntity, COMPONENT_RENDERABLE))->isRenderable = false;
            ((Model*)getComponent(chestOpenEntity, COMPONENT_RENDERABLE))->isRenderable = true;
            switch (click_counter) {
                case 0:
                    RenderText("Coffre         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Tu as trouvé une épée dans le coffre.   ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("Elle pourrait s'avérer utile en chemin. ", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
                    if (getMouseButtonState(1) && !is_clicking) {
                        click_counter = 0;
                        *isBusy = false;
                        ((Model*)getComponent(swordEntity, COMPONENT_RENDERABLE))->isRenderable = true;
                        enemyModel->isRenderable = true;
                        is_clicking = true;
                        checkpoint_sword = true;
                        playerComponent->hasWeapon = true;
                    }
                    if (!getMouseButtonState(1)) {
                        is_clicking = false;
                    }
            }
            playerAnimator->currentAnimation = (Animation*)getAnimationComponent(playerEntity, "playerIdleAnimation");
        }


        if (x < -13.0f && x > -18.0f && y < -8.0f && y > -13.0f && !*isBusy) {
            RenderText("Appuyer sur E pour interagir", color_white, gameState->g_WindowWidth /2, gameState->g_WindowHeight / 15 + 50, 20, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            if (getKeyState(SDLK_e)) {
                *isBusy = true;
            }
        } else if (x < -13.0f && x > -18.0f && y < -8.0f && y > -13.0f && *isBusy) {
            talkToMarchandMain(inventory, marchantInventory ,gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program, &click_counter, &is_clicking, isBusy, &gameState->money);
        }

    
}





void unloadStartScene(Scene* scene){
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