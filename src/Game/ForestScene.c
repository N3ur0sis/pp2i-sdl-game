#include "ForestScene.h"


/*
Entity of this scene (order of their index):
    Moon Light 
    Map
    Player
    Sword
    Enemy
    Flame 1
    Flame 2
    Flame 3
    Flame 4
    Light 1 
    Dungeon Door
*/


void ForestMainScene(Scene* scene, GameState* gameState){
    float x;
    float y;
    float z;
    float rot;
    switch (gameState->previousSceneIndex){
        case(1) ://from dungeon
            x = -6.0;
            y = 10.1;
            z = 168.0;
            rot = glm_rad(180.0f);
            break;
        default :
            x = 1.0;
            y = 10.1;
            z = 32.0;
            rot = 0;
            break;
    }
    /* Load and compile shaders */
    scene->shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    /* Load and compile textShader */
    scene->textShader = LoadShaders("assets/shaders/text.vs","assets/shaders/text.fs");
    UseShaders(scene->shader);
    /* Create a scene camera */
    scene->camera = camera_create(x, y+5, z, gameState->g_WindowWidth, gameState->g_WindowHeight);
    glUniform3fv(scene->shader->m_locations.cameraPosition, 1, scene->camera->Position);
    /* Create a skybox */
    scene->skybox = SkyboxCreate();

    /* Light Entity */
    Entity* lightEntity = createEntity(scene);
    if (lightEntity != NULL) {
        Light* light = LightCreate(scene->shader, (vec4){1.0, 1.0, 1.8, 0}, (vec3){ 0.3f, 0.3f, 0.4f }, 0.0001f, 0.1f,-1000.0f,500.0f);
        addComponent(lightEntity, COMPONENT_LIGHT, light);
    }

    /* Map Entity */
    Entity* mapEntity = createEntity(scene);
    if (mapEntity != NULL) {
        Model* map = (Model*)calloc(1, sizeof(Model));
        ModelCreate(map,"assets/models/Foret/forest.obj");
        addComponent(mapEntity, COMPONENT_RENDERABLE, map);

        Collider* mapCollision = ColliderCreate("assets/models/Foret/col.obj");
        glm_translate_make(mapCollision->transformMatrix, (vec3){0.0f, -1.0f, 0.0f});
        UpdateCollider(mapCollision);
        addComponent(mapEntity, COMPONENT_COLLIDER, mapCollision);
    }

    /* Player Entity */
    Entity* playerEntity = create_player(scene,x,y,z);
    Model* playerModel = getComponent(playerEntity,COMPONENT_RENDERABLE);
    playerModel->rotation[1] = rot;

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

    /* Enemy Entity */
    Entity* gobelin = create_gobelin(scene,0.0f,10.1f,50.0f,0.5f);


    /*Flame Entity*/
    Entity* flame1 = createEntity(scene);
    if (flame1){
        Model* flame = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame->isRenderable = false;
         }  
        glm_vec3_copy((vec3){50.5f,9.8f,112.0f},flame->position);
        addComponent(flame1, COMPONENT_RENDERABLE, flame);
        /*
        //Light* light = LightCreate(scene->shader, (vec4){50.5f,-100.8f,112.0f,0}, (vec3){1.0f, 0.8f, 0.0f }, 0.5f,  0.15f,0.1f,5.0f);
        Light* light = LightCreate(scene->shader, (vec4){50.5f,-100.8f,112.0f,0}, (vec3){0.5, 0.4, 0.2}, 1.0f, 0.9f, 0.1f, 500.0f);
        addComponent(flame1, COMPONENT_LIGHT, light);*/
        
    }
    Entity* flame2 = createEntity(scene);
    if (flame2){
        Model* flame_2 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_2, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_2->isRenderable = false;
         }  
        glm_vec3_copy((vec3){62.3f,9.8f,156.0f},flame_2->position);
        addComponent(flame2, COMPONENT_RENDERABLE, flame_2);
        
    }
    Entity* flame3 = createEntity(scene);
    if (flame3){
        Model* flame_3 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_3, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_3->isRenderable = false;
         }  
        glm_vec3_copy((vec3){-59.0f,9.8f,146.50f},flame_3->position);
        addComponent(flame3, COMPONENT_RENDERABLE, flame_3);
        
    }
    Entity* flame4 = createEntity(scene);
    if (flame4){
        Model* flame_4 = (Model*)calloc(1, sizeof(Model));
        ModelCreate(flame_4, "assets/models/Foret/Flame.obj");
        if (!gameState->isForestDungeonDone){
        flame_4->isRenderable = false;
         }   
        glm_vec3_copy((vec3){-64.7f,9.8f,72.0f},flame_4->position);
        addComponent(flame4, COMPONENT_RENDERABLE, flame_4);
        
    }
    Entity* DungeonDoor = createEntity(scene);
    if (DungeonDoor){
        Model* DungeonDoorModel = (Model*)calloc(1, sizeof(Model));
        ModelCreate(DungeonDoorModel, "assets/models/Foret/DungeonForestDoor.obj");
        //glm_vec3_copy((vec3){-6.7f,9.8f,169.0f},DungeonDoorModel->position);
        addComponent(DungeonDoor, COMPONENT_RENDERABLE, DungeonDoorModel);
        
    }/*
    Entity* helmethornEntity = createEntity(scene);
    if (helmethornEntity != NULL) {
        Model* helmet = (Model*)calloc(1, sizeof(Model));
        ModelCreate(helmet, "assets/models/Equipement/Hornhelmet.obj");
        addComponent(helmethornEntity, COMPONENT_RENDERABLE, helmet);

        AttachmentComponent* helmetAttachment = (AttachmentComponent*)calloc(1, sizeof(AttachmentComponent));
        helmetAttachment->boneIndex = 7; // Example bone index
        helmetAttachment->parentAnimator = (Animator*)getComponent(gobelin, COMPONENT_ANIMATOR);
        helmetAttachment->parentModel = (Model*)getComponent(gobelin, COMPONENT_RENDERABLE);
        glm_vec3_copy((vec3){-10.75f, 0.0f, -9.5f}, helmetAttachment->offsetPosition);
        glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, helmetAttachment->offsetRotation);
        glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, helmetAttachment->offsetScale);
        addComponent(helmethornEntity, COMPONENT_ATTACHMENT, helmetAttachment);
    }*/
    /*
    Entity* swordGobEntity = createEntity(scene);
    if (swordGobEntity != NULL) {
        Model* sword = (Model*)calloc(1, sizeof(Model));
        ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
        addComponent(swordGobEntity, COMPONENT_RENDERABLE, sword);

        AttachmentComponent* swordAttachment = (AttachmentComponent*)calloc(1, sizeof(AttachmentComponent));
        swordAttachment->boneIndex = 0; // Example bone index
        swordAttachment->parentAnimator = (Animator*)getComponent(gobelin, COMPONENT_ANIMATOR);
        swordAttachment->parentModel = (Model*)getComponent(gobelin, COMPONENT_RENDERABLE);
        glm_vec3_copy((vec3){-12.1f, -1.35f, -9.5f}, swordAttachment->offsetPosition);
        glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, swordAttachment->offsetRotation);
        glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, swordAttachment->offsetScale);
        addComponent(swordGobEntity, COMPONENT_ATTACHMENT, swordAttachment);
    }
    */
   /*
    Entity* spearGobEntity = createEntity(scene);
    if (spearGobEntity != NULL) {
        Model* spear = (Model*)calloc(1, sizeof(Model));
        ModelCreate(spear, "assets/models/Equipement/spear.obj");
        addComponent(spearGobEntity, COMPONENT_RENDERABLE, spear);

        AttachmentComponent* spearAttachment = (AttachmentComponent*)calloc(1, sizeof(AttachmentComponent));
        spearAttachment->boneIndex = 0; // Example bone index
        spearAttachment->parentAnimator = (Animator*)getComponent(gobelin, COMPONENT_ANIMATOR);
        spearAttachment->parentModel = (Model*)getComponent(gobelin, COMPONENT_RENDERABLE);
        glm_vec3_copy((vec3){-12.1f, 0.f, -9.0f}, spearAttachment->offsetPosition);
        glm_vec3_copy((vec3){20.0f, 40.0f, 0.0f}, spearAttachment->offsetRotation);
        glm_vec3_copy((vec3){1.0f, 1.0f, 1.0f}, spearAttachment->offsetScale);
        addComponent(spearGobEntity, COMPONENT_ATTACHMENT, spearAttachment);
    }*/
    

    

}
void updateForestScene(Scene* scene, GameState* gameState){
    // Game Logic
    bool isClicking = false;
    Camera* camera =scene->camera; 
    Entity* playerEntity = &scene->entities[2];
    Entity* mapEntity = &scene->entities[1];
    Entity* dungeonDoorEntity = &scene->entities[9];
    Model* dungeonDoorModel = (Model*)getComponent(dungeonDoorEntity, COMPONENT_RENDERABLE);
    Model* playerModel = (Model*)getComponent(playerEntity, COMPONENT_RENDERABLE);
    Animator* playerAnimator = (Animator*)getComponent(playerEntity, COMPONENT_ANIMATOR);
    Collider* playerCollider = (Collider*)getComponent(playerEntity, COMPONENT_COLLIDER);

    if(!((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || playerAnimator->currentAnimation == (Animation*)getAnimationComponent(playerEntity, "playerAttackAnimation"))){
        playerAnimator->playTime = 0.0f;
    }
    if (!playerModel->isBusy){
        playerMovement(playerEntity, scene->deltaTime, scene->camera, NULL);
        }
    
    if (getKeyState(SDLK_p)){
        printf("Player Position : %f %f\n",playerModel->position[0],playerModel->position[2]);
    }
    /*Four flames logic */
    SDL_Color color_black = {0, 0, 0, 0};
    Entity* flame1 = &scene->entities[5];
    Model* flame1Model = (Model*)getComponent(flame1, COMPONENT_RENDERABLE);
    Entity* flame2 = &scene->entities[6];
    Model* flame2Model = (Model*)getComponent(flame2, COMPONENT_RENDERABLE);
    Entity* flame3 = &scene->entities[7];
    Model* flame3Model = (Model*)getComponent(flame3, COMPONENT_RENDERABLE);
    Entity* flame4 = &scene->entities[8];
    Model* flame4Model = (Model*)getComponent(flame4, COMPONENT_RENDERABLE);
    if (!flame1Model->isRenderable){
        float d1 = getDist(playerModel,flame1Model);
        if ((d1<FLAMEDIST&&getKeyState(SDLK_e))){
            flame1Model->isRenderable = true;
            playerModel->isBusy = true;
        }
    }
    if (!flame2Model->isRenderable){
        float d2 = getDist(playerModel,flame2Model);
        if ((d2<FLAMEDIST&&getKeyState(SDLK_e))){
            flame2Model->isRenderable = true;
            playerModel->isBusy = true;  
        }
        
    }
    if (!flame3Model->isRenderable){
        float d3 = getDist(playerModel,flame3Model);
        if ((d3<FLAMEDIST&&getKeyState(SDLK_e))){
            flame3Model->isRenderable = true;
            playerModel->isBusy = true;
            
        }
    }
    if (!flame4Model->isRenderable){
         float d4 = getDist(playerModel,flame4Model);
         if ((d4<FLAMEDIST&&getKeyState(SDLK_e))){
            flame4Model->isRenderable = true;
            playerModel->isBusy = true;
            
        }
    }
    if (playerModel->isBusy&&dungeonDoorModel->position[1]==0.0f){
        RenderText("Vous entendez un bruit sourd au loin", color_black, gameState->g_WindowWidth / 2 - 115, gameState->g_WindowHeight / 15 + 100, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1)){
            playerModel->isBusy = false;
        }
    }
    if (flame1Model->isRenderable&&flame2Model->isRenderable&&flame3Model->isRenderable&&flame4Model->isRenderable){
        if (dungeonDoorModel->isRenderable){
            if (dungeonDoorModel->position[1]>10.0f){
                dungeonDoorModel->isRenderable = false;
                 playerModel->isBusy = false;
            }
            else{
                glm_vec3_copy((vec3){-6.0f,30.0f,160.0f},camera->Position);
                camera->Yaw = 90.0f;
                dungeonDoorModel->position[1]+=0.01f;
                playerModel->isBusy = true;
            }
        }else{
            vec3 DonjonPosition ;
            vec3 DonjonDir;
            glmc_vec3_copy((vec3){-7.4f,10.0f, 168.69f},DonjonPosition);
            glm_vec3_sub( playerModel->position, DonjonPosition, DonjonDir);
            float DonjonDist = glm_vec3_norm(DonjonDir);
            if (DonjonDist<1.0f&&getKeyState(SDLK_e)){
                gameState->change = true;
                gameState ->nextSceneIndex = 1;
                gameState->previousSceneIndex = 2;
        }}
        
    }
    vec3 mainPos= {-0.5, 10.1, 25.0};
    vec3 mainDir;
    glm_vec3_sub(playerModel->position,mainPos,mainDir);
    if (glm_vec3_norm(mainDir)<3.0f){
        gameState->change = true;
        gameState->nextSceneIndex = 3;
        gameState->previousSceneIndex = 2;
    }

}

void unloadForestScene(Scene* scene){
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