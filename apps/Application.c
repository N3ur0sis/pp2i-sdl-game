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


/* Global variable, only for things that won't change during the game or used for intitialization */
static const int g_WindowWidth = 1280;
static const int g_WindowHeight = 720;
static const char* g_WindowTitle = "Game";

void StartSceneUpdate();
void StartSceneLoad();
void StartSceneUnload();
void StartSceneRender(Scene scene, Shader* shader, Camera* camera);


/* Entry point of the program */
int main(void){

    /* Create a instance of the application */
    Application* game = ApplicationCreate(g_WindowWidth, g_WindowHeight, g_WindowTitle);

    /* Load and compile shaders */
    Shader* shader = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");
    

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
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->playerModel->scale);
    glm_vec3_copy((vec3){28.0f,0.1f,7.0f},player->playerModel->position);

    /* Sword */
    Model* sword = (Model*)calloc(1, sizeof(Model));
    ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");

    /* Map */
    Model* map = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/start/start.obj");

    /* Collision*/
    Model* tree = (Model*)calloc(1, sizeof(Model));
    ModelCreate(tree, "assets/models/start/col.obj");
    glm_vec3_copy((vec3){0.0f,-0.5f,0.0f},tree->position);

    /* Lights*/
    Light *light = LightCreate(shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5,0.4,0.2},1.0f, 0.9f);

    /* Create a scene camera */
    Camera* camera = camera_create(player->playerModel->position[0], player->playerModel->position[1]+17.5f, player->playerModel->position[2]-17.5f, g_WindowWidth, g_WindowHeight);
    glUniform3fv(shader->m_locations.cameraPosition,1,camera->Position);

    /* Create a skybox */
    Skybox* skybox = SkyboxCreate();


    /* Temp variables */
    bool enemyIsAttacking = false;
    bool playerIsAttacking = false;
    float playerHealth = 100.0f;


    /* Game Loop */
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    while(game->running) {

        StartFrame(game);
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;




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
                player->playerAnimator->currentAnimation = attackAnimation;
                player->playerAnimator->playTime = 0.0f;
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




        /* Shadow Rendering */
        glEnable(GL_DEPTH_TEST);
        glViewport(0,0,2048,2048);
        glBindFramebuffer(GL_FRAMEBUFFER,light->shadowMap->depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        UseShaders(light->shadowMap->shadowMapShader);
        ModelDraw(map,light->shadowMap->shadowMapShader,camera);
        ModelDraw(player->playerModel,light->shadowMap->shadowMapShader,camera);
        ModelDraw(golem,light->shadowMap->shadowMapShader,camera);
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glViewport(0,0,g_WindowWidth,g_WindowHeight);

        /* Entity Rendering */    
        UseShaders(shader);
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, light->shadowMap->depthMap);
        glUniform1i(glGetUniformLocation(shader->m_program, "shadowMap"), 6);
        if((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || player->playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
        }else if(player->playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
        }else{
            AnimatorOnUpdate(player->playerAnimator,player->playerModel,shader,deltaTime);
            player->playerAnimator->playTime = 0.0f;
        }

        glUniform1i(glGetUniformLocation(shader->m_program,"isAnimated"), player->playerModel->isAnimated);
        ModelDraw(player->playerModel, shader, camera);
        AnimatorOnUpdate(golemAnimator,golem,shader,deltaTime);
        glUniform1i(glGetUniformLocation(shader->m_program,"isAnimated"), golem->isAnimated);
        ModelDraw(golem, shader, camera);

        /* Scene Rendering */
        glUniform1i(glGetUniformLocation(shader->m_program,"isAnimated"), map->isAnimated);
        glActiveTexture(GL_TEXTURE0 + 6);
        glBindTexture(GL_TEXTURE_2D, light->shadowMap->depthMap);
        glUniform1i(glGetUniformLocation(shader->m_program, "shadowMap"), 6);
        ModelDraw(map, shader, camera);
        glm_mat4_dup(player->playerModel->modelMatrix, sword->modelMatrix);
        mat4 offsetMatrix;
        glm_translate_make(offsetMatrix,(vec3){-1.3f,-0.7f,0.3f});
        glm_mat4_mul(sword->modelMatrix,player->playerAnimator->currentAnimation->bone_anim_mats[21],sword->modelMatrix);
        glm_mat4_mul(sword->modelMatrix,offsetMatrix,sword->modelMatrix);
        glUniformMatrix4fv(shader->m_locations.Model, 1, GL_FALSE, (float*)sword->modelMatrix);
        glUniform1i(glGetUniformLocation(shader->m_program,"isAnimated"), sword->isAnimated);
        ModelDrawAttached(sword, shader, camera);

        glBindVertexArray(0);

        /* Light Rendering */
        UseShaders(shader);
        LightUpdate(shader, light);

        /* Rendering SkyBox */
        SkyboxDraw(skybox,camera);


        EndFrame(game);
    }



    /* Clean every ressources allocated */
    ModelFree(player->playerModel);
    ModelFree(map);
    free(camera);
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
}