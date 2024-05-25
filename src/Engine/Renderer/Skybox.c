#include <Skybox.h>
Skybox* NightSkyboxCreate(void){

    Skybox* skybox = (Skybox*)calloc(1,sizeof(Skybox));
    skybox->shader = LoadShaders("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
    char* faces[6] =
    {
    "assets/images/nightbox/px.png",
    "assets/images/nightbox/nx.png",
    "assets/images/nightbox/py.png",
    "assets/images/nightbox/ny.png",
    "assets/images/nightbox/pz.png",
    "assets/images/nightbox/nz.png"
    };
    skybox->cubemapTexture = CubeMapLoad(faces);  

    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};




    glGenVertexArrays(1, &skybox->skyboxVAO);
    glGenBuffers(1, &skybox->skyboxVBO);
    glBindVertexArray(skybox->skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skybox->skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return skybox;
}
Skybox* SkyboxCreate(void){

    Skybox* skybox = (Skybox*)calloc(1,sizeof(Skybox));
    skybox->shader = LoadShaders("assets/shaders/skybox.vs", "assets/shaders/skybox.fs");
    char* faces[6] =
    {
    "assets/images/skybox/right.png",
    "assets/images/skybox/left.png",
    "assets/images/skybox/top.png",
    "assets/images/skybox/bottom.png",
    "assets/images/skybox/front.png",
    "assets/images/skybox/back.png"
    };
    skybox->cubemapTexture = CubeMapLoad(faces);  

    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};




    glGenVertexArrays(1, &skybox->skyboxVAO);
    glGenBuffers(1, &skybox->skyboxVBO);
    glBindVertexArray(skybox->skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skybox->skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return skybox;
}

void    SkyboxDraw(Skybox* skybox, Camera* camera){
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_CULL_FACE);
        UseShaders(skybox->shader);
        mat4 cameraView;
        getViewMatrix(camera, cameraView); 
        mat3 subView;
        glm_mat4_pick3(cameraView, subView);
        mat4 view;
        glm_mat4_zero(view);
        glm_mat4_ins3(subView,view);
        glUniformMatrix4fv(skybox->shader->m_locations.View, 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(skybox->shader->m_locations.Projection, 1, GL_FALSE, (float*)camera->projectionMatrix);
        glBindVertexArray(skybox->skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
}
void    SkyboxDelete(Skybox* skybox){
    if (skybox){

    DeleteShaders(skybox->shader);
    free(skybox);
    }
}