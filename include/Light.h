/**
 * @file Light.h
 * @brief Header file for the light component.
*/

#pragma once

#include <cglm/cglm.h>
#include <Shader.h>
#include <ShadowMap.h>

/**
 * @brief Struct representing a light.
 * 
 * This struct represents a light.
 * 
 */
typedef struct _Light {
    vec4 position;              /**< Position of the light. */  
    vec3 intensity;             /**< Color of the light. */
    float attenuation;          /**< Attenuation of the light. */
    float ambientCoefficient;   /**< Ambient coefficient of the light. */
    ShadowMap* shadowMap;       /**< Shadow map of the light. */
} Light;

/**
 * @brief Function to create a light.
 * 
 * This function creates a light.
 * 
 * @param S Pointer to the shader.
 * @param position Position of the light.
 * @param intensity Intensity of the light.
 * @param attenuation Attenuation of the light.
 * @param ambientCoef Ambient coefficient of the light.
 * @param nearz Near z value of the light.
 * @param farz Far z value of the light.
 * @return Pointer to the light.
 */
Light* LightCreate(Shader *S, vec4 position, vec3 intensity, float attenuation, float ambientCoef,float nearz, float farz);

/**
 * @brief Function to update the light.
 * 
 * This function updates the light.
 * 
 * @param S Pointer to the shader.
 * @param point Pointer to the light.
 */
void LightUpdate(Shader *S, Light *point);