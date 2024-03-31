#include <Engine.h>
#include <Shader.h>
#include <Camera.h>
#include <Model.h>
#include <Light.h>
#include <Textures.h>
#include <Skybox.h>

#define sogv_gl_uniform_set_mat4x4(SHADER, UNIFORM, MAT4X4) glUniformMatrix4fv(glGetUniformLocation(SHADER, UNIFORM), 1, GL_FALSE, &MAT4X4[0][0])
#define sogv_gl_uniform_set_mat4x4_v(SHADER, COUNT, UNIFORM, MAT4X4) glUniformMatrix4fv(glGetUniformLocation(SHADER, UNIFORM), COUNT, GL_FALSE, &MAT4X4[0][0])


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
    //player->position[1] += 2.0f;
    glm_vec3_copy((vec3){0.5f,0.5f,0.5f},player->scale);
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
    mat4x4 anim[MAX_BONES];
    for(size_t i=0; i<MAX_BONES; ++i){
        mat4x4_identity(anim[i]);
    }
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
        mat4x4 bones;
        mat4x4_identity(bones);
        char name[64];
        for(size_t i=0; i<MAX_BONES; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)bones);
        }

        mat4x4 test;
        mat4x4_identity(test);
        anim_time += deltaTime*player->anim_ticks;
        if(anim_time>=player->anim_dur) anim_time -= player->anim_dur;
        sogv_skel_animate(player->root_node, anim_time, test, player->bones, anim);
        for(size_t i=0; i<player->bone_count; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)anim[i]);
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
