#include <ShadowMap.h>

ShadowMap* ShadowMapCreate(vec3 position, Shader* shader){

    ShadowMap* shadowMap = (ShadowMap*)calloc(1,sizeof(ShadowMap));
    shadowMap->shadowMapShader = LoadShaders("assets/shaders/shadowMap.vs", "assets/shaders/shadowMap.fs");
    glGenFramebuffers(1, &    shadowMap->depthMapFBO);
    glGenTextures(1, &shadowMap->depthMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap->depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 2048, 2048, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap->depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap->depthMap, 0);
    glDrawBuffer(GL_NONE); // No color buffer is drawn to.
    glReadBuffer(GL_NONE);
    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;

    mat4 orthoProj, lightView;
    vec3 lighPos;
    glm_vec3_scale(position, 30.0f, lighPos);
    glm_ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 500.0f,orthoProj);
    glm_lookat( lighPos, (vec3){0.0f,0.0f,0.0f},(vec3){0.0f,1.0f,0.0f}, lightView);
    glm_mat4_mul(orthoProj,lightView,shadowMap->depthMatrix);

    UseShaders(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader->m_program,"depthMVP"), 1, GL_FALSE,(float*)shadowMap->depthMatrix);
    UseShaders(shadowMap->shadowMapShader);
    glUniformMatrix4fv(glGetUniformLocation(shadowMap->shadowMapShader->m_program,"depthMVP"), 1, GL_FALSE,(float*)shadowMap->depthMatrix);
    

    return shadowMap;
}