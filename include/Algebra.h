/**
* @file Algebra.h
* @brief Implementations of algebra functions.
*
* This file contains the implementations of algebra functions.
*/

#pragma once
#include <assimp/cimport.h>
#include <cglm/cglm.h>

/**
 * @brief Converts an assimp vector to a glm vector.
 * 
 * This function converts an assimp vector to a glm vector.
 * 
 * @param vec The glm vector.
 * @param ai_vec The assimp vector.
 */
void AssimpVec3(vec3 vec, struct aiVector3D ai_vec);

/**
 * @brief Converts an assimp quaternion to a glm quaternion.
 * 
 * This function converts an assimp quaternion to a glm quaternion.
 * 
 * @param q The glm quaternion.
 * @param ai_q The assimp quaternion.
 */
void AssimpQuat(versor q, struct aiQuaternion ai_q);

/**
 * @brief Converts an assimp matrix to a glm matrix.
 * 
 * This function converts an assimp matrix to a glm matrix.
 * 
 * @param mat The glm matrix.
 * @param ai_mat The assimp matrix.
 */
void AssimpMat4(mat4 mat, struct aiMatrix4x4 ai_mat);