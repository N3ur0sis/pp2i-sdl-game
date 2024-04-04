#include <Light.h>
#include <stdlib.h>
#include <stdio.h>



Light* LightCreate(Shader *S, vec4 position, vec3 intensity, float attenuation, float ambientCoef) {
	Light *light = (Light*)malloc(sizeof(Light));

	glm_vec3_copy(position,light->position);
	glm_vec3_copy(intensity, light->intensity);
	light->attenuation = attenuation;
	light->ambientCoefficient = ambientCoef;

	LightUpdate(S, light);

	return light;
}

void LightUpdate(Shader *S, Light *light) {

	glUniform4fv(S->m_locations.lightPosition,1, (GLfloat*)light->position);
	glUniform3fv(S->m_locations.lightIntensity, 1, (GLfloat*)light->intensity);
	glUniform1f(S->m_locations.lightAttenuation, light->attenuation);
	glUniform1f(S->m_locations.lightAmbienbtCoef, light->ambientCoefficient);
}