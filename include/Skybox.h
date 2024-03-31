#pragma once
#include <Shader.h>
#include <Textures.h>
#include <cglm/cglm.h>
#include <Camera.h>

typedef struct _Skybox{
        unsigned int skyboxVAO;
        unsigned int skyboxVBO;
        unsigned int cubemapTexture;
        char* faces[6];
        Shader* shader;

}Skybox;


Skybox* SkyboxCreate(void);
void    SkyboxDraw(Skybox* skybox, Camera* camera);
void    SkyboxDelete(Skybox* skybox);
