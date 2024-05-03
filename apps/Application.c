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
    Model* player = (Model*)calloc(1, sizeof(Model));
    ModelCreate(player, "assets/models/LoPotitChat/Walking.dae");
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->scale);
    //glm_vec3_copy((vec3){0.5f,10.0f,-4.5f},player->position);

    Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/Walking.dae", player);
    Animator* playerAnimator = AnimatorCreate(walkingAnimation);
    Model* map = (Model*)calloc(1, sizeof(Model));
    Model* tree = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/start/start.obj");
    ModelCreate(tree, "assets/models/start/col.obj");
    Animator* goblinAnimator = AnimatorCreate(goblinIdleAnimation);
    
    glm_vec3_copy((vec3){0.0f,0.1f,0.0f},player->position);
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
    
    float anim_time = 0.0f;
    float anim_time2 = 0.0f;

    /* Game Loop */
    while(game->running) {
        StartFrame(game);


        vec3 enemyDir;
        glm_vec3_sub(player->position, goblin->position, enemyDir);
        glm_vec3_normalize(enemyDir);
        if(enemyDir[0] != .0f || enemyDir[1] != .0f || enemyDir[2] != .0f){
        goblinAnimator->currentAnimation = goblinWalkingAnimation;
	    float omega = acos(glm_dot((vec3){0,0,1},enemyDir));
	    if (enemyDir[0] < 0) {
	    	omega = -omega;
	    }
	    float currentAngleDeg = glm_deg(goblin->rotation[1]);
        float targetAngleDeg = glm_deg(omega);

        // Ensure the that the fucking target angle is within the range of -180 to 180 degrees (i spent three fucking hours just to realize the angles wasn't normalized , fuck me!)
        while (targetAngleDeg - currentAngleDeg > 180) {
            targetAngleDeg -= 360;
        }
        while (targetAngleDeg - currentAngleDeg < -180) {
            targetAngleDeg += 360;
        }

        // Perform linear interpolation
        float rotTarget = glm_lerp(currentAngleDeg, targetAngleDeg, 0.1f);
        goblin->rotation[1] = glm_rad(rotTarget);
        }
        glm_vec3_scale(enemyDir,2*deltaTime,enemyDir);
	    glm_vec3_add(goblin->position,enemyDir,goblin->position);

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        treatMovingInput(player->position, player->rotation, deltaTime, camera, playerbb,playerbbo, treebb, tree);

        printf("%f,%f,%f\n", player->position[0],player->position[1], player->position[2]);

        /* Rendering Scene */
        UseShaders(shader);
        mat4 bones;
        glm_mat4_identity(bones);
        char name[64];
        for(size_t i=0; i<MAX_BONES; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)bones);
        }
        
        if(getKeyState(SDLK_z) || getKeyState(SDLK_d) || getKeyState(SDLK_q) || getKeyState(SDLK_s)){
            anim_time += deltaTime*walkingAnimation->anim_ticks;
        }else{
            anim_time = 0.0f;
        }

        mat4 identity;
        glm_mat4_identity(identity);
        if(anim_time>=walkingAnimation->anim_dur) anim_time -= walkingAnimation->anim_dur;
        CalculateBoneTransformation(playerAnimator->currentAnimation->root_node, anim_time, identity, player->bones, walkingAnimation->bone_anim_mats);
        for(size_t i=0; i<player->bone_count; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)walkingAnimation->bone_anim_mats[i]);
        }
        ModelDraw(player, shader, camera);

        glm_mat4_identity(bones);
        for(size_t i=0; i<MAX_BONES; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)bones);
        }
        glm_mat4_identity(identity);
        anim_time2 += deltaTime*goblinAnimator->currentAnimation->anim_ticks;
        if(anim_time2>=goblinAnimator->currentAnimation->anim_dur) anim_time2 -= goblinAnimator->currentAnimation->anim_dur;
        CalculateBoneTransformation(goblinAnimator->currentAnimation->root_node, anim_time2, identity, goblin->bones, goblinAnimator->currentAnimation->bone_anim_mats);
        for(size_t i=0; i<goblin->bone_count; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)goblinAnimator->currentAnimation->bone_anim_mats[i]);
        }
        //ModelDraw(goblin, shader, camera);
        (void)goblinAnimator;
        (void)goblinIdleAnimation;
        (void)anim_time2;


        UseShaders(shader2);
        ModelDraw(map, shader2, camera);
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

