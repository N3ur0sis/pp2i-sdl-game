#pragma once

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_shader_content(const char* fileName);
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

