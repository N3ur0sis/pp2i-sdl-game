#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>
#include <Textures.h>
#include <Skybox.h>
#include <Animator.h>
#include <Controls.h>


/* Global variable, only for things that won't change during the game */
static const int g_WindowWidth = 1280;
static const int g_WindowHeight = 720;
static const char* g_WindowTitle = "Game";

/* Entry point of the program */
int main(void){

    /* Create a instance of the application */
    Application* game = ApplicationCreate(g_WindowWidth, g_WindowHeight, g_WindowTitle);

    /* Load and compile shaders */
    Shader* shader = LoadShaders("assets/shaders/anim.vs", "assets/shaders/default.fs");
    Shader* shader2 = LoadShaders("assets/shaders/default.vs", "assets/shaders/default.fs");

    /* Start Function, create objects in scene */
    Model* goblin = (Model*)calloc(1, sizeof(Model));
    ModelCreate(goblin, "assets/models/Goblin/Mutant Breathing Idle.dae");
    printf("%ld", goblin->bone_count);
    Animation* goblinIdleAnimation = AnimationCreate("assets/models/Goblin/Mutant Breathing Idle.dae", goblin);
    Animation* goblinWalkingAnimation = AnimationCreate("assets/models/Goblin/Mutant Walking.dae", goblin);
    Animation* goblinPunchAnimation = AnimationCreate("assets/models/Goblin/Mutant Punch.dae", goblin);
    Model* player = (Model*)calloc(1, sizeof(Model));
    ModelCreate(player, "assets/models/LoPotitChat/Walking.dae");
    Model* sword = (Model*)calloc(1, sizeof(Model));
    ModelCreate(sword, "assets/models/LoPotitChat/sword.obj");
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->scale);
    //glm_vec3_copy((vec3){0.5f,10.0f,-4.5f},player->position);

    Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/Walking.dae", player);
    Animation* attackAnimation = AnimationCreate("assets/models/LoPotitChat/Sword And Shield Attack.dae", player);
    Animator* playerAnimator = AnimatorCreate(walkingAnimation);
    Model* map = (Model*)calloc(1, sizeof(Model));
    Model* tree = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/start/start.obj");
    ModelCreate(tree, "assets/models/start/col.obj");
    Animator* goblinAnimator = AnimatorCreate(goblinIdleAnimation);
    
    glm_vec3_copy((vec3){28.0f,0.1f,7.0f},player->position);
    glm_vec3_copy((vec3){2.0f,0.0f,-10.0f},goblin->position);
    glm_vec3_copy((vec3){0.0f,-0.5f,0.0f},tree->position);
    mat4 id;


    
	Light *light = LightCreate(shader2, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.4,0.4,0.2},1.0f, 0.9f);
    Light *light2 = LightCreate(shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5,0.4,0.2},1.0f, 0.9f);
        vec3 playerbbo[2] = {
        {player->meshes[0].aabb.mMin.x,
        player->meshes[0].aabb.mMin.y,
        player->meshes[0].aabb.mMin.z},
        {player->meshes[0].aabb.mMax.x,
        player->meshes[0].aabb.mMax.y,
        player->meshes[0].aabb.mMax.z}
    };

        vec3 playerbb[2] = {
        {player->meshes[0].aabb.mMin.x,
        player->meshes[0].aabb.mMin.y,
        player->meshes[0].aabb.mMin.z},
        {player->meshes[0].aabb.mMax.x,
        player->meshes[0].aabb.mMax.y,
        player->meshes[0].aabb.mMax.z}
    };
    vec3 treebb[2];
    glm_scale_make(id,(vec3){0.5f,0.5f,0.5f});
    glm_aabb_transform(playerbb,id,playerbb);
    glm_aabb_transform(playerbbo,id,playerbbo);
    /* Create a scene camera */
    Camera* camera = camera_create(player->position[0], player->position[1]+17.5f, player->position[2]-17.5f, g_WindowWidth, g_WindowHeight);
    glUniform3fv(shader2->m_locations.cameraPosition,1,camera->Position);
    glUniform3fv(shader->m_locations.cameraPosition,1,camera->Position);

    /* Create a skybox */
    Skybox* skybox = SkyboxCreate();

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    bool enemyIsAttacking = false;
    bool playerIsAttacking = false;
    float playerHealth = 100.0f;



    /* Game Loop */
    while(game->running) {

        StartFrame(game);
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;




        float rotTarget= 0.0f;
        vec3 enemyDir;
        glm_vec3_sub(player->position, goblin->position, enemyDir);
        float enemyDist = glm_vec3_norm(enemyDir);
        glm_vec3_normalize(enemyDir);
        if(enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f){
	        float omega = acos(glm_dot((vec3){0,0,1},enemyDir));
	    if (enemyDir[0] < 0) {
	    	omega = -omega;
	    }

        if(getMouseButtonState(1) && !playerIsAttacking){
                playerIsAttacking = true;
                playerAnimator->currentAnimation = attackAnimation;
                playerAnimator->playTime = 0.0f;
        }else if(!playerIsAttacking){
            playerAnimator->currentAnimation = walkingAnimation;
        }
        if(playerAnimator->playTime > playerAnimator->currentAnimation->anim_dur - 10 && playerIsAttacking){
                playerIsAttacking = false;
                playerAnimator->playTime = 0.0f;
            }

	    float currentAngleDeg = glm_deg(goblin->rotation[1]);
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
                goblinAnimator->playTime = 0.0f;
                goblinAnimator->currentAnimation = goblinPunchAnimation;
            }
            if(goblinAnimator->playTime > goblinAnimator->currentAnimation->anim_dur - 10){
                    playerHealth -= 10.0f;
                    goblinAnimator->playTime = 0.0f;
                    enemyIsAttacking = false;
            }
                    goblin->rotation[1] = glm_rad(rotTarget);

        }else if(enemyDist < 15.0f){
        goblin->rotation[1] = glm_rad(rotTarget);
        enemyIsAttacking = false;
        goblinAnimator->currentAnimation = goblinWalkingAnimation;
        glm_vec3_scale(enemyDir,2*deltaTime,enemyDir);
	    glm_vec3_add(goblin->position,enemyDir,goblin->position);
        }else{
        enemyIsAttacking = false;
        goblinAnimator->currentAnimation = goblinIdleAnimation;
        }

        treatMovingInput(player->position, player->rotation, deltaTime, camera, playerbb,playerbbo, treebb, tree);




    
        UseShaders(shader);
        if((getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)) || playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(playerAnimator,player,shader,deltaTime);
        }else if(playerAnimator->currentAnimation == attackAnimation){
            AnimatorOnUpdate(playerAnimator,player,shader,deltaTime);
        }else{
            AnimatorOnUpdate(playerAnimator,player,shader,deltaTime);
            playerAnimator->playTime = 0.0f;
        }
        ModelDraw(player, shader, camera);

        AnimatorOnUpdate(goblinAnimator,goblin,shader,deltaTime);
        ModelDraw(goblin, shader, camera);




        UseShaders(shader2);
        ModelDraw(map, shader2, camera);
        glm_mat4_dup(player->modelMatrix, sword->modelMatrix);
        mat4 offsetMatrix;
        glm_translate_make(offsetMatrix,(vec3){-1.3f,-0.7f,0.3f});
        glm_mat4_mul(sword->modelMatrix,walkingAnimation->bone_anim_mats[21],sword->modelMatrix);
        glm_mat4_mul(sword->modelMatrix,offsetMatrix,sword->modelMatrix);
        glUniformMatrix4fv(shader2->m_locations.Model, 1, GL_FALSE, (float*)sword->modelMatrix);
        ModelDrawAttached(sword, shader2, camera);
        //ModelDraw(tree, shader2, camera);
        glBindVertexArray(0);
        cameraControl(camera);
        LightUpdate(shader2, light);
        UseShaders(shader);
        LightUpdate(shader, light2);

        /* Rendering SkyBox */
        SkyboxDraw(skybox,camera);


        EndFrame(game);
    }

    /* Clean every ressources allocated */
    ModelFree(player);
    ModelFree(map);
    free(camera);
    DeleteShaders(shader);
    SkyboxDelete(skybox);
    WindowDelete(game->window);
    EngineQuit();
}

