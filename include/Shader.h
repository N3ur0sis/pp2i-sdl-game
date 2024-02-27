#pragma once

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct shaderLocations {
	GLuint View;
    GLuint Projection;
    GLuint Model;
} shaderLocations;

typedef struct shader {
	GLuint program;
	shaderLocations locations;
} Shader;

char* get_shader_content(const char* fileName);
Shader* LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
void useShaders(GLuint program);

