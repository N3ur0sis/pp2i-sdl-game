#include <System.h>

void renderSystem(Scene* scene) {
    glEnable(GL_DEPTH_TEST);

    // Render shadow maps for each light
    for (int i = 0; i < scene->numEntities; ++i) {
        Entity* lightEntity = &scene->entities[i];
        Light* light = (Light*)getComponent(lightEntity, COMPONENT_LIGHT);
        if (light && light->shadowMap) {
            glViewport(0, 0, 2048, 2048);
            glBindFramebuffer(GL_FRAMEBUFFER, light->shadowMap->depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            UseShaders(light->shadowMap->shadowMapShader);

            for (int j = 0; j < scene->numEntities; ++j) {
                Entity* entity = &scene->entities[j];
                Model* model = (Model*)getComponent(entity, COMPONENT_RENDERABLE);
                if (model) {
                    glUniform1i(glGetUniformLocation(light->shadowMap->shadowMapShader->m_program, "isAnimated"), model->isAnimated);
                    ModelDraw(model, light->shadowMap->shadowMapShader, scene->camera, NULL);
                }
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }

    // Reset viewport
    glViewport(0, 0, g_WindowWidth, g_WindowHeight);

    // Render skybox
    SkyboxDraw(scene->skybox, scene->camera);

    // Render all entities with the main scene shader
    UseShaders(scene->shader);

    for (int i = 0; i < scene->numEntities; ++i) {
        Entity* entity = &scene->entities[i];
        Model* model = (Model*)getComponent(entity, COMPONENT_RENDERABLE);
        if (model) {
            Animator* animator = (Animator*)getComponent(entity, COMPONENT_ANIMATOR);
            if (animator) {
                AnimatorOnUpdate(animator, model, scene->shader, scene->deltaTime);
            }

            AttachmentComponent* attachment = (AttachmentComponent*)getComponent(entity, COMPONENT_ATTACHMENT);
            if (attachment) {
                mat4 customModelMatrix;
                glm_mat4_dup(attachment->parentModel->modelMatrix, customModelMatrix);
                mat4 offsetMatrix;
                glm_translate_make(offsetMatrix, attachment->offsetPosition);
                glm_mat4_mul(customModelMatrix, attachment->parentAnimator->currentAnimation->bone_anim_mats[attachment->boneIndex], customModelMatrix);
                glm_mat4_mul(customModelMatrix, offsetMatrix, customModelMatrix);
                glUniform1i(glGetUniformLocation(scene->shader->m_program, "isAnimated"), model->isAnimated);
                ModelDraw(model, scene->shader, scene->camera, customModelMatrix);
            } else {
                glUniform1i(glGetUniformLocation(scene->shader->m_program, "isAnimated"), model->isAnimated);
                ModelDraw(model, scene->shader, scene->camera, NULL);
            }
        }
    }

    // Render lights
    for (int i = 0; i < scene->numEntities; ++i) {
        Entity* entity = &scene->entities[i];
        Light* light = (Light*)getComponent(entity, COMPONENT_LIGHT);
        if (light) {
            LightUpdate(scene->shader, light);
        }
    }
}
