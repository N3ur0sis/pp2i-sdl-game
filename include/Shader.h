/**
 * @file Shader.h
 * @brief Header file for the shader component.
*/

#pragma once
#include <glad/glad.h>
#include <ReadShader.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct for storing shader uniform locations.
 */
typedef struct _shaderLocations {
	GLuint View;				/**< Location of the view matrix uniform */
    GLuint Projection;			/**< Location of the projection matrix uniform */
    GLuint Model;				/**< Location of the model matrix uniform */
	GLuint lightPosition;		/**< Location of the light position uniform */
	GLuint lightIntensity;		/**< Location of the light intensity uniform */
	GLuint lightAttenuation;	/**< Location of the light attenuation uniform */
	GLuint lightAmbienbtCoef;	/**< Location of the light ambient coefficient uniform */
	GLuint cameraPosition;		/**< Location of the camera position uniform */
} ShaderLocations;

/**
 * @brief Struct for storing shader program.
 */
typedef struct _Shader {
	GLuint m_program;			/**< Shader program */
	ShaderLocations m_locations;	/**< Shader locations */
} Shader;

/**
 * @brief Loads vertex and fragment shaders from files and creates a shader program.
 *
 * @param vertex_file_path Path to the vertex shader file.
 * @param fragment_file_path Path to the fragment shader file.
 * @return Pointer to the created Shader struct.
 */
Shader* LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

/**
 * @brief Uses the specified shader program.
 *
 * @param shader Pointer to the Shader struct to be used.
 */
void UseShaders(Shader* shader);

/**
 * @brief Deletes the specified shader program and frees associated resources.
 *
 * @param shader Pointer to the Shader struct to be deleted.
 */
void DeleteShaders(Shader* shader);
