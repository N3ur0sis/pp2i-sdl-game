#include <Light.h>
#include <stdlib.h>
#include <stdio.h>



Light* LightCreate(Shader *S, vec4 position, vec3 intensity, float attenuation, float ambientCoef,float nearz, float farz,float ortho) {
	Light *light = (Light*)malloc(sizeof(Light));

	glm_vec3_copy(position,light->position);
	glm_vec3_copy(intensity, light->intensity);
	light->attenuation = attenuation;
	light->ambientCoefficient = ambientCoef;
	light->shadowMap = ShadowMapCreate(position, S,nearz,farz,ortho);
	LightUpdate(S, light);
	UseShaders(S);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, light->shadowMap->depthMap);
    glUniform1i(glGetUniformLocation(S->m_program, "shadowMap"), 2);
	return light;
}

void LightUpdate(Shader *S, Light *light) {

	glUniform4fv(S->m_locations.lightPosition,1, (GLfloat*)light->position);
	glUniform3fv(S->m_locations.lightIntensity, 1, (GLfloat*)light->intensity);
	glUniform1f(S->m_locations.lightAttenuation, light->attenuation);
	glUniform1f(S->m_locations.lightAmbienbtCoef, light->ambientCoefficient);
}

