#include <Animator.h>

Animator* AnimatorCreate(Animation* animation){
    Animator* animator = (Animator*)calloc(1,sizeof(Animator)) ;
    animator->currentAnimation = animation;
    animator->playTime = 0.0f;
    return animator;
}

void AnimatorOnUpdate(Animator* animator, Model* model,Shader* shader, float deltaTime){
        char name[64];
        mat4 identity;
        glm_mat4_identity(identity);
        animator->playTime += deltaTime*animator->currentAnimation->anim_ticks;
        if(animator->playTime>=animator->currentAnimation->anim_dur) animator->playTime -= animator->currentAnimation->anim_dur;
        CalculateBoneTransformation(animator->currentAnimation->root_node, animator->playTime, identity, model->bones, animator->currentAnimation->bone_anim_mats);
        for(size_t i=0; i<model->bone_count; ++i) {
            sprintf(name, "bones_mat[%zu]", i);
            glUniformMatrix4fv(glGetUniformLocation(shader->m_program, name), 1, GL_FALSE, (float*)animator->currentAnimation->bone_anim_mats[i]);
        }
}