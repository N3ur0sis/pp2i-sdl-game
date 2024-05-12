#pragma once
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <Shader.h>

typedef struct _ShadowMap{
    GLuint depthMapFBO;
    GLuint depthMap;
    mat4 depthMatrix;
    Shader* shadowMapShader;
} ShadowMap;


ShadowMap* ShadowMapCreate(vec3 position, Shader* shader);