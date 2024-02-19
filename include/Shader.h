#ifndef LOAD_SHADER_H
#define LOAD_SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_shader_content(const char* fileName);
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);


#endif // LOAD_SHADER_H
