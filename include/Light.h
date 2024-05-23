#pragma once

#include <cglm/cglm.h>
#include <Shader.h>
#include <ShadowMap.h>

typedef struct _Light {
    vec4 position;
    vec3 intensity; //a.k.a. the color of the light
    float attenuation;
    float ambientCoefficient;
    ShadowMap* shadowMap;
} Light;


Light* LightCreate(Shader *S, vec4 position, vec3 intensity, float attenuation, float ambientCoef,float nearz, float farz);
void LightUpdate(Shader *S, Light *point);