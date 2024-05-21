#pragma once
#include <Animation.h>

typedef struct _Animator{
    Animation* currentAnimation;
    float playTime;
}Animator;

Animator* AnimatorCreate(Animation* animation);
void AnimatorOnUpdate(Animator* animator, Model* model,Shader* shader, float deltaTime);
void FreeAnimator(Animator* animator);