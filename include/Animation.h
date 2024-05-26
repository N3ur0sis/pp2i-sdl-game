/*
* @file Animation.h
* @brief Implementations of animation functions.
*
* This file contains the implementations of animation functions.
*/

#pragma once
#include <Model.h>

/**
 * @brief Structure representing a node in the skeleton.
 * 
 * This structure represents a node in the skeleton.
*/
typedef struct Animation {
    Node* root_node;    /**< Root node of the animation. */
    mat4 parent_mat;    /**< Parent transformation matrix */
    mat4* bone_mats;    /**< Array of bone matrices */
    mat4* bone_anim_mats;   /**< Array of bone animation matrices */
    float anim_dur;     /**< Duration of the animation */
    float anim_ticks;   /**< Ticks per second of the animation */
    char * name;        /**< Name of the animation */
} Animation;

/**
 * @brief Creates a new Animation instance.
 * 
 * @param path The path to the model file.
 * @param model The model to animate.
 * @param name The name of the animation.
 * @return Pointer to the created Animation instance or NULL on failure.
 */
Animation* AnimationCreate(char* path, Model* model, char* name);

/**
 * @brief Calculates the bone transformation.
 * 
 * This function calculates the bone transformation.
 * 
 * @param node The node to calculate the transformation for.
 * @param anim_time The time of the animation.
 * @param parent_mat The parent matrix.
 * @param bones The array of bone matrices.
 * @param bone_anim_mats The array of bone animation matrices.
 */
void CalculateBoneTransformation(Node* node, float anim_time, mat4 parent_mat, mat4* bones,mat4* bone_anim_mats);

/**
 * @brief Finds a node in the skeleton.
 * 
 * This function finds a node in the skeleton.
 * 
 * @param root The root node.
 * @param name The name of the node.
 * @return Pointer to the found node or NULL if not found.
 */
Node* NodeFind(Node* root, const char* name);

/**
 * @brief Imports a node from an assimp node.
 * 
 * This function imports a node from an assimp node.
 * 
 * @param ai_node The assimp node.
 * @param skel_node The skeleton node.
 * @param bone_count The number of bones.
 * @param bone_names The array of bone names.
 * @return 0 on success, 1 on failure.
 */
int NodeImport(const struct aiNode* ai_node, Node** skel_node, size_t bone_count, char bone_names[][256]);

/**
 * @brief Deletes a node.
 * 
 * This function deletes a node.
 * 
 * @param node The node to delete.
 */
void NodeDelete(Node* node);

/**
 * @brief Deletes an animation.
 * 
 * This function deletes an animation.
 * 
 * @param animation The animation to delete.
 */
void AnimationDelete(Animation* animation);