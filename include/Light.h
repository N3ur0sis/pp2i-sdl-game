#pragma once

#include <cglm/cglm.h>
#include <Shader.h>

typedef struct pointLight {
	vec3 color;
	vec3 position;
	float intensity;
	float attenuation;
} pointLight;

void light_setAmbientLight(Shader *S, vec3 color, float intensity);

pointLight* light_createPointLight(Shader *S, vec3 color, vec3 position, float intensity, float attenuation);
void light_updatePointLight(Shader *S, pointLight *point);