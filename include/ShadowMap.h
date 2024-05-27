/**
 * @file ShadowMap.h
 * @brief Header file for the shadow map component.
*/

#pragma once
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <Shader.h>

/**
 * @brief Struct representing a shadow map.
 * 
 * This struct represents a shadow map.
*/
typedef struct _ShadowMap{
    GLuint depthMapFBO;         /**< Framebuffer object for the depth map. */
    GLuint depthMap;            /**< Depth map. */
    mat4 depthMatrix;           /**< Depth matrix. */
    Shader* shadowMapShader;    /**< Shader for the shadow map. */
} ShadowMap;

/**
 * @brief Function to create a shadow map.
 * 
 * This function creates a shadow map.
 * 
 * @param position Position of the shadow map.
 * @param shader Shader for the shadow map.
 * @param nearz Near z value.
 * @param farz Far z value.
 * @return Pointer to the shadow map.
 */
ShadowMap* ShadowMapCreate(vec3 position, Shader* shader,float nearz, float farz);