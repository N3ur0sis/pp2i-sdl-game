#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>
#include <Textures.h>
#include <Skybox.h>
#include <Animator.h>
#include <Controls.h>
#include <SceneManager.h>
#include <Dungeon.h>
#include <SDL_mixer.h>
 
/* Global variable, only for things that won't change during the game or used for intitialization */
static const int g_WindowWidth = 1280;
static const int g_WindowHeight = 720;
static const char* g_WindowTitle = "Game";

void StartSceneUpdate();
void StartSceneLoad();
void StartSceneUnload();
void StartSceneRender(Scene scene, Shader* shader, Camera* camera);

struct Glyph {
    Model model;
    float advance;
};


/* Entry point of the program */
int main(void){

    /* Create a instance of the application */
    Application* game = ApplicationCreate(g_WindowWidth, g_WindowHeight, g_WindowTitle);    
    /* Load and compile shaders */
    Shader* shader = LoadShaders("assets/shaders/anim.vs", "assets/shaders/default.fs");
    Shader* shader2 = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    Shader* shader3 = LoadShaders("assets/shaders/shadowMap.vs", "assets/shaders/shadowMap.fs");
    //Music
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Failed to initialize SDL audio: %s\n", SDL_GetError());
    return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    Mix_Music *bgm = Mix_LoadMUS("assets/music/my-little-garden-of-eden-112845.mp3");
    if (bgm == NULL) {
    fprintf(stderr, "Failed to load background music: %s\n", Mix_GetError());
    return -1;
    }

    if (Mix_PlayMusic(bgm, -1) == -1) {  
    fprintf(stderr, "SDL_mixer could not play music! SDL_mixer Error: %s\n", Mix_GetError());
    return -1;
    }
    Mix_VolumeMusic(10); // 64=50% du volume

    //Sound 
    Mix_Chunk *attackSound = Mix_LoadWAV("assets/sound/swing.wav");
    if (attackSound == NULL) {
        fprintf(stderr, "Failed to load attack sound: %s\n", Mix_GetError());
        return -1;
    }
    SceneManager* sceneManager = (SceneManager*)calloc(1, sizeof(SceneManager));

    Scene startScene = {.modelComponents = NULL,.entities=0,.loadScene=StartSceneLoad,.unloadScene=StartSceneUnload,.updateScene=StartSceneUpdate,.renderScene=StartSceneRender};
    ModelCreate(&startScene.modelComponents[startScene.entities++], "assets/models/LoPotitChat/sword.obj");

    /* Start Function, create objects in scene */
    /* Enemy */
    Model* golem = (Model*)calloc(1, sizeof(Model));
    ModelCreate(golem, "assets/models/Golem/Mutant Breathing Idle.dae");
    Animation* golemIdleAnimation = AnimationCreate("assets/models/Golem/Mutant Breathing Idle.dae", golem);
    Animation* golemWalkingAnimation = AnimationCreate("assets/models/Golem/Mutant Walking.dae", golem);
    Animation* golemPunchAnimation = AnimationCreate("assets/models/Golem/Mutant Punch.dae", golem);
    Animator* golemAnimator = AnimatorCreate(golemIdleAnimation);
    glm_vec3_copy((vec3){2.0f,0.0f,-10.0f},golem->position);

    /* Player*/
    Player* player = playerCreate("assets/models/LoPotitChat/PlayerWalk.dae");
    Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerAttack.dae", player->playerModel);
    Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/PlayerWalk.dae", player->playerModel);
    Animator* playerAnimator = AnimatorCreate(walkingAnimation);
    player->playerAnimator = playerAnimator;
    glm_vec3_copy((vec3){0.4f,0.4f,0.4f},player->playerModel->scale);
    glm_vec3_copy((vec3){-2.0f,0.0f,-4.0f},player->playerModel->position);

    /* Sword */
    Model* sword = (Model*)calloc(1, sizeof(Model));
    ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
    /* Dungeon*/
    Dungeon * dj = dj_create();
    initialize(dj);
    initializeRooms(dj);
    Affiche(dj);
    float lastopen =0.0f;
    /* Map */
    Model* map = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/start/start.obj");

    /* Collision*/
    Model* tree = (Model*)calloc(1, sizeof(Model));
    ModelCreate(tree, "assets/models/start/col.obj");
    glm_vec3_copy((vec3){0.0f,-0.5f,0.0f},tree->position);
    Model* chest = (Model*)calloc(1, sizeof(Model));
    ModelCreate(chest, "assets/models/Objet/Chest/ChestFermeSerrure.obj");
    bool isOpen = false;
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f},chest->position);
    glm_vec3_copy((vec3){0.75f,0.75f,0.75f},chest->scale);
    chest->rotation[1] = glm_rad(180.0f);
    Model* chest2 = (Model*)calloc(1, sizeof(Model));
    ModelCreate(chest2,"assets/models/Objet/Chest/ChestOuvert.obj");
    glm_vec3_copy((vec3){0.0f,0.0f,0.0f},chest2->position);
    glm_vec3_copy((vec3){0.75f,0.75f,0.75f},chest2->scale);
    chest2->rotation[1] = glm_rad(180.0f);
    /* Lights*/
	Light *light = LightCreate(shader2, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.4,0.4,0.2},1.0f, 0.9f);
    Light *light2 = LightCreate(shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5,0.4,0.2},1.0f, 0.9f);

    /* Create a scene camera */
    Camera* camera = camera_create(player->playerModel->position[0], player->playerModel->position[1]+17.5f, player->playerModel->position[2]-17.5f, g_WindowWidth, g_WindowHeight);
    glUniform3fv(shader2->m_locations.cameraPosition,1,camera->Position);
    glUniform3fv(shader->m_locations.cameraPosition,1,camera->Position);

    /* Create a skybox */
    Skybox* skybox = SkyboxCreate();


    /* Temp variables */
    bool enemyIsAttacking = false;
    bool playerIsAttacking = false;
    float playerHealth = 100.0f;
    float ennmyHealth = 100.0f;


    /* Shadow Impl test*/
    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
 GLuint FramebufferName = 0;
 glGenFramebuffers(1, &FramebufferName);

 // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
 GLuint depthTexture;
 glGenTextures(1, &depthTexture);
 glBindTexture(GL_TEXTURE_2D, depthTexture);
 glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 2048, 2048, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

 glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
 glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

 glDrawBuffer(GL_NONE); // No color buffer is drawn to.
 glReadBuffer(GL_NONE);
 // Always check that our framebuffer is ok
 if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    return false;


mat4 orthoProj, lightView, lighProj;
vec3 lighPos;
glm_vec3_scale((vec3){1.0, 1.0, -0.8}, 30.0f, lighPos);
glm_ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 500.0f,orthoProj);
glm_lookat( lighPos, (vec3){0.0f,0.0f,0.0f},(vec3){0.0f,1.0f,0.0f}, lightView);
glm_mat4_mul(orthoProj,lightView,lighProj);




    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    while(game->running) {

        StartFrame(game);
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;



        glEnable(GL_DEPTH_TEST);
        glViewport(0,0,2048,2048);
        glBindFramebuffer(GL_FRAMEBUFFER,FramebufferName);
        glClear(GL_DEPTH_BUFFER_BIT);
        UseShaders(shader3);
        glUniformMatrix4fv(glGetUniformLocation(shader3->m_program,"depthMVP"), 1, GL_FALSE,(float*)lighProj);
        ModelDraw(player->playerModel,shader3,camera);
        ModelDraw(golem,shader,camera);
        glBindFramebuffer(GL_FRAMEBUFFER,0);


        glViewport(0,0,g_WindowWidth,g_WindowHeight);

        /* Game Logic */
        float rotTarget= 0.0f;
        vec3 enemyDir;
        glm_vec3_sub(player->playerModel->position, golem->position, enemyDir);
        float enemyDist = glm_vec3_norm(enemyDir);
        glm_vec3_normalize(enemyDir);
        if(enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f){
	        float omega = acos(glm_dot((vec3){0,0,1},enemyDir));
	    if (enemyDir[0] < 0) {
	    	omega = -omega;
	    }
        if(getMouseButtonState(1) && !playerIsAttacking){
                playerIsAttacking = true;
                Mix_PlayChannel(-1, attackSound, 0);
                player->playerAnimator->currentAnimation = attackAnimation;
                player->playerAnimator->playTime = 0.0f;
                if (10>enemyDist){
                    ennemyHealth-=50.0f;
                }
                if (ennmyHealth<=0){
                    printf("Golem is dead\n");
                }
        }else if(!playerIsAttacking){
            player->playerAnimator->currentAnimation = walkingAnimation;
        }
        if(player->playerAnimator->playTime > player->playerAnimator->currentAnimation->anim_dur - 10 && playerIsAttacking){
                playerIsAttacking = false;
                player->playerAnimator->playTime = 0.0f;
            }
	    float currentAngleDeg = glm_deg(golem->rotation[1]);
        float targetAngleDeg = glm_deg(omega);
        while (targetAngleDeg - currentAngleDeg > 180) {
            targetAngleDeg -= 360;
        }
        while (targetAngleDeg - currentAngleDeg < -180) {
            targetAngleDeg += 360;
        }
        rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);
        }
        if( enemyDist < 3.0f){
            if(!enemyIsAttacking){
                enemyIsAttacking = true;
                golemAnimator->playTime = 0.0f;
                golemAnimator->currentAnimation = golemPunchAnimation;
            }
            if(golemAnimator->playTime > golemAnimator->currentAnimation->anim_dur - 10){
                    playerHealth -= 10.0f;
                    golemAnimator->playTime = 0.0f;
                    enemyIsAttacking = false;
            }
                    golem->rotation[1] = glm_rad(rotTarget);
        }else if(enemyDist < 15.0f){
        golem->rotation[1] = glm_rad(rotTarget);
        enemyIsAttacking = false;
        golemAnimator->currentAnimation = golemWalkingAnimation;
        glm_vec3_scale(enemyDir,2*deltaTime,enemyDir);
	    glm_vec3_add(golem->position,enemyDir,golem->position);
        }else{
        enemyIsAttacking = false;
        golemAnimator->currentAnimation = golemIdleAnimation;
        }

        playerMovement(player,deltaTime,camera,tree, golem);
        cameraControl(camera);
        if (getKeyState(SDLK_p)){
        printf("x = %f,y = %f\n",player->playerModel->position[0],player->playerModel->position[2]);
    }
        if (dj->state){
        if (getKeyState(SDLK_b)){
            printf("La direction d'ou on vient est %c, et %d et l id est %d\n",dj->direction,dj->current_room,dj->rooms[dj->current_room].id);
        }
        vec3 ChestDir;
            glm_vec3_sub(player->playerModel->position, chest->position, ChestDir);
            float ChestDist = glm_vec3_norm(ChestDir);
            if (ChestDist<1.0f&&playerInteract()&&(SDL_GetTicks()-lastopen)>=1000.0f&&!isOpen ){
                lastopen = SDL_GetTicks();
                isOpen = true;
                printf("le joueur ouvre le coffre !\n");
            }
        switch(dj->rooms[dj->current_room].id){
            
            case 0:
            LogicRoom1C(dj,player );
            break;
            case 1:
            LogicRoom2C(dj,player );
            break;
            case 2:
            LogicRoom2I(dj,player );
            break;
            case 3:
            LogicRoom2L(dj,player );
            break;
            case 4:
            LogicRoom3C(dj,player );
            break;
            case 5:
            LogicRoom3T(dj,player );
            break;
            case 6:
            LogicRoom4C(dj,player );
            break;
            case 7:
            LogicRoomB(dj,player);
            break;
        }
        if (dj->change){
                dj->lastRoomChangeTime = SDL_GetTicks();
                LoadRoom(player,dj);
                dj->change = false;
            }
        }
    
        if (!dj->state && getKeyState(SDLK_h)){
            dj->state = true;
            LoadRoom(player,dj);
            printf("On entre dans le donjon\n");
        }
        startScene.updateScene();
        startScene.renderScene(startScene,shader2,camera);
        /* Entity Rendering */    
        UseShaders(shader);
        glUniformMatrix4fv(glGetUniformLocation(shader->m_program,"depthMVP"), 1, GL_FALSE,(float*)lighProj);
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glUniform1i(glGetUniformLocation(shader->m_program, "shadowMap"), 6);
        if((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || player->playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
        }else if(player->playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
        }else{
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
            player->playerAnimator->playTime = 0.0f;
        }

        ModelDraw(player->playerModel, shader, camera);
        AnimatorOnUpdate(golemAnimator,golem,shader,deltaTime);
        ModelDraw(golem, shader, camera);

        /* Scene Rendering */
        UseShaders(shader2);
        glUniformMatrix4fv(glGetUniformLocation(shader2->m_program,"depthMVP"), 1, GL_FALSE,(float*)lighProj);
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glUniform1i(glGetUniformLocation(shader2->m_program, "shadowMap"), 6);
        if (!dj->state){
            ModelDraw(map, shader2, camera);
        }
        else{ModelDraw(dj->type_room[dj->rooms[dj->current_room].id].model, shader2, camera);
            if (!isOpen){
            ModelDraw(chest,shader2,camera);}
            else{ModelDraw(chest2,shader2,camera);};
}
        glm_mat4_dup(player->playerModel->modelMatrix, sword->modelMatrix);
        mat4 offsetMatrix;
        glm_translate_make(offsetMatrix,(vec3){-1.3f,-0.7f,0.3f});
        glm_mat4_mul(sword->modelMatrix,player->playerAnimator->currentAnimation->bone_anim_mats[21],sword->modelMatrix);
        glm_mat4_mul(sword->modelMatrix,offsetMatrix,sword->modelMatrix);
        glUniformMatrix4fv(shader2->m_locations.Model, 1, GL_FALSE, (float*)sword->modelMatrix);
        ModelDrawAttached(sword, shader2, camera);

        glBindVertexArray(0);

        /* Light Rendering */
        LightUpdate(shader2, light);
        UseShaders(shader);
        LightUpdate(shader, light2);

        /* Rendering SkyBox */
        SkyboxDraw(skybox,camera);


        EndFrame(game);
    }



    /* Clean every ressources allocated */
    ModelFree(player->playerModel);
    ModelFree(map);
    ModelFree(tree);
    ModelFree(chest);
    ModelFree(chest2);
    ModelFree(golem);
    freeDungeon(dj);
    free(camera);
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(attackSound);
    bgm = NULL;

    Mix_CloseAudio();
    DeleteShaders(shader);
    SkyboxDelete(skybox);
    WindowDelete(game->window);
    EngineQuit();
}



void StartSceneUpdate(){
    //printf("Update Start Scene");
}
void StartSceneLoad(){
    //printf("Load Start Scene");
    
}
void StartSceneUnload(){
    //printf("Unload Start Scene");

}
void StartSceneRender(Scene scene, Shader* shader, Camera* camera){
    //printf("Render Start Scene");
    UseShaders(shader);
    ModelDraw(&scene.modelComponents[0], shader,camera );
}