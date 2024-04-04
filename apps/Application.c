#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>
#include <Textures.h>
#include <Skybox.h>
#include <Animator.h>
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
    Model* player = (Model*)calloc(1, sizeof(Model));
    ModelCreate(player, "assets/models/LoPotitChat/Walking.dae");
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->scale);

    Animation* walkingAnimation = AnimationCreate("assets/models/LoPotitChat/Walking.dae", player);
    Animator* playerAnimator = AnimatorCreate(walkingAnimation);
    Model* map = (Model*)calloc(1, sizeof(Model));
    ModelCreate(map, "assets/models/map/map.obj");

	Light *light = LightCreate(shader2, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5,0.4,0.2},1.0f, 0.9f);
    Light *light2 = LightCreate(shader, (vec4){1.0, 1.0, -0.8, 0}, (vec3){0.5,0.4,0.2},1.0f, 0.9f);
    
    /* Create a scene camera */
    Camera* camera = camera_create(player->position[0], player->position[1]+17.5f, player->position[2]-17.5f, g_WindowWidth, g_WindowHeight);
    glUniform3fv(shader2->m_locations.cameraPosition,1,camera->Position);
    glUniform3fv(shader->m_locations.cameraPosition,1,camera->Position);

    /* Create a skybox */
    Skybox* skybox = SkyboxCreate();

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;
    
    float anim_time = 0.0f;
    /* Game Loop */
    while(game->running) {
        StartFrame(game);


        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        treatMovingInput(player->position, player->rotation, deltaTime, camera);



        /* Rendering Scene */
        UseShaders(shader);
        mat4 bones;
        glm_mat4_identity(bones);
        char name[64];
        for(size_t i=0; i<MAX_BONES; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)bones);
        }

        mat4 identity;
        glm_mat4_identity(identity);
        anim_time += deltaTime*walkingAnimation->anim_ticks;
        if(anim_time>=walkingAnimation->anim_dur) anim_time -= walkingAnimation->anim_dur;
        CalculateBoneTransformation(playerAnimator->currentAnimation->root_node, anim_time, identity, player->bones, walkingAnimation->bone_anim_mats);
        for(size_t i=0; i<player->bone_count; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)walkingAnimation->bone_anim_mats[i]);
        }
        ModelDraw(player, shader, camera);



        UseShaders(shader2);
        ModelDraw(map, shader2, camera);
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

