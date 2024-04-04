#pragma once
#include <glad/glad.h>
#include <ReadShader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _shaderLocations {
	GLuint View;
    GLuint Projection;
    GLuint Model;
	GLuint lightPosition;
	GLuint lightIntensity;
	GLuint lightAttenuation;
	GLuint lightAmbienbtCoef;
	GLuint cameraPosition;
} ShaderLocations;

typedef struct _Shader {
	GLuint m_program;
	ShaderLocations m_locations;
} Shader;


Shader* LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
void UseShaders(Shader* shader);
void DeleteShaders(Shader* shader);
