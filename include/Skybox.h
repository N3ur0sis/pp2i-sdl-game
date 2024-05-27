/**
 * @file Skybox.h
 * @brief Header file for the skybox component.
*/

#pragma once
#include <Shader.h>
#include <Textures.h>
#include <cglm/cglm.h>
#include <Camera.h>

/**
 * @brief Struct representing a skybox.
 * 
 * This struct represents a skybox.
*/
typedef struct _Skybox{
        unsigned int skyboxVAO;         /**< Vertex array object for the skybox. */
        unsigned int skyboxVBO;         /**< Vertex buffer object for the skybox. */
        unsigned int cubemapTexture;    /**< Cubemap texture. */
        char* faces[6];                 /**< Array of faces. */
        Shader* shader;                 /**< Shader for the skybox. */
}Skybox;

/**
 * @brief Function to create a skybox.
 * 
 * This function creates a skybox.
 * 
 * @return Pointer to the skybox.
*/
Skybox* SkyboxCreate(void);

/**
 * @brief Function to create a night skybox.
 * 
 * This function creates a night skybox.
 * 
 * @return Pointer to the skybox.
*/
Skybox* NightSkyboxCreate(void);

/**
 * @brief Function to draw the skybox.
 * 
 * This function draws the skybox.
 * 
 * @param skybox Pointer to the skybox.
 * @param camera Pointer to the camera.
*/
void    SkyboxDraw(Skybox* skybox, Camera* camera);

/**
 * @brief Function to delete the skybox.
 * 
 * This function deletes the skybox.
 * 
 * @param skybox Pointer to the skybox.
*/
void    SkyboxDelete(Skybox* skybox);
