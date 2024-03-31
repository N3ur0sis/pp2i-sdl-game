#pragma once
#include <glad/glad.h>

typedef struct _Texture {
    unsigned int id;
    char* type;
} Texture;  


GLuint load_textures(const char* texturePath);
GLuint loadCubemap(char** faces);