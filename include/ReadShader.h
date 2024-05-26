/**
 * @file ReadShader.h
 * @brief Header file for the read shader component.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Function to get the content of a shader.
 * 
 * This function gets the content of a shader.
 * 
 * @param fileName Name of the file.
 * @return Content of the shader.
 */
char* get_shader_content(const char* fileName);
