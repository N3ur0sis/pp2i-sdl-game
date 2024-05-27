/**
 * @file Textures.h
 * @brief Header file for the Textures module.
*/

#pragma once
#include <glad/glad.h>


/**
 * @brief Represent a single texture in the engine. Can be used by multiple Objet, 
 * completely dissociated from any Model, this class is just the reuslt of loading an image into a buffer.
 * @note It uses the default texture unit, hence it is not necessary to specify the uniform value on the shader.
*/
typedef struct _Texture {
    GLuint id;              /**< Holds the id of the texture object, used to bind the texure before rendering */
    const char* type;       /**< Type of the texture map, ex. DIFFUSE, SPECULAR, NORMAL, ROUGHNESS */
} Texture;  

/**
 * @brief Load a texture from a file.
 * 
 * This function loads a texture from a file.
 * 
 * @param texturePath Path to the texture file.
 * @return GLuint ID of the texture.
 */
GLuint TextureLoad(const char* texturePath);

/**
 * @brief Load a cubemap texture.
 * 
 * This function loads a cubemap texture.
 * 
 * @param faces Array of faces.
 * @return GLuint ID of the cubemap texture.
 */
GLuint CubeMapLoad(char** faces);