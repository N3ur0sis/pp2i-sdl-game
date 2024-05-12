#include <Animator.h>

Animator* AnimatorCreate(Animation* animation){
    Animator* animator = (Animator*)calloc(1,sizeof(Animator)) ;
    animator->currentAnimation = animation;
    return animator;
}
