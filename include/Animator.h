/**
 * @file Animator.h
 * @brief Animator header file
 */

#pragma once
#include <Animation.h>

/**
 * @brief Structure representing an animator.
 * 
 * This structure represents an animator.
*/
typedef struct _Animator{
    Animation* currentAnimation;    /**< Current animation */
    float playTime;                 /**< Time of the animation */
}Animator;

/**
 * @brief Creates a new Animator instance.
 * 
 * @param animation The animation to animate.
 * @return Pointer to the created Animator instance or NULL on failure.
 */
Animator* AnimatorCreate(Animation* animation);

/**
 * @brief Updates the animator.
 * 
 * This function updates the animator.
 * 
 * @param animator The animator to update.
 * @param model The model to animate.
 * @param shader The shader to use.
 * @param deltaTime The time since the last frame.
 */
void AnimatorOnUpdate(Animator* animator, Model* model,Shader* shader, float deltaTime);

/**
 * @brief Frees the animator.
 * 
 * This function frees the animator.
 * 
 * @param animator The animator to free.
 */
void FreeAnimator(Animator* animator);