#pragma once
#include <glad/glad.h>


/**
 * Represent a single texture in the engine. Can be used by multiple Objet, 
 * completely dissociated from any Model, this class is just the reuslt of loading an image into a buffer.
 * @note It uses the default texture unit, hence it is not necessary to specify the uniform value on the shader.
*/
typedef struct _Texture {
    GLuint id;              /* Holds the id of the texture object, used to bind the texure before rendering */
    const char* type;       /* Type of the texture map, ex. DIFFUSE, SPECULAR, NORMAL, ROUGHNESS */
} Texture;  


GLuint TextureLoad(const char* texturePath);
GLuint CubeMapLoad(char** faces);