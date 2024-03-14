#include <Light.h>
#include <stdlib.h>
#include <stdio.h>

void light_setAmbientLight(Shader *S, vec3 color, float intensity) {
	glUniform3fv(S->locations.ambientLightColor, 1, (GLfloat*)color);
	glUniform1f(S->locations.ambientLightIntensity, intensity);
}

pointLight* light_createPointLight(Shader *S, vec3 color, vec3 position, float intensity, float attenuation) {
	pointLight *point = (pointLight*)malloc(sizeof(pointLight));

	glm_vec3_copy(color,point->color);
	glm_vec3_copy(position, point->position);

	point->intensity = intensity;
	point->attenuation = attenuation;

	light_updatePointLight(S, point);

	return point;
}

void light_updatePointLight(Shader *S, pointLight *point) {
	glUniform3fv(S->locations.pointLightColor,1, (GLfloat*)point->color);
	glUniform3fv(S->locations.pointLightPosition, 1, (GLfloat*)point->position);
	glUniform1f(S->locations.pointLightIntensity, point->intensity);
	glUniform1f(S->locations.pointLightAttenuation, point->attenuation);
}
