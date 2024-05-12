#pragma once
#include <Animation.h>

typedef struct _Animator{
    Animation* currentAnimation;
}Animator;

Animator* AnimatorCreate(Animation* animation);

