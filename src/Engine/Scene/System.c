#include <System.h>

void renderSystem(Scene* scene, GameState* gamestate) {
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
                if (model && model->isRenderable) {
                    glUniform1i(glGetUniformLocation(light->shadowMap->shadowMapShader->m_program, "isAnimated"), model->isAnimated);
                    ModelDraw(model, light->shadowMap->shadowMapShader, scene->camera, NULL);
                }
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }

    // Reset viewport
    glViewport(0, 0, gamestate->g_WindowWidth, gamestate->g_WindowHeight);

    // Render skybox
    SkyboxDraw(scene->skybox, scene->camera);

    // Render all entities with the main scene shader
    UseShaders(scene->shader);

    for (int i = 0; i < scene->numEntities; ++i) {
        Entity* entity = &scene->entities[i];
        Model* model = (Model*)getComponent(entity, COMPONENT_RENDERABLE);
        Dungeon* dj = (Dungeon*)getComponent(entity, COMPONENT_DUNGEON);
        if (dj) {  
            glUniform1i(glGetUniformLocation(scene->shader->m_program, "isAnimated"), dj->type_room[dj->rooms[dj->current_room].id].model->isAnimated);
            ModelDraw(dj->type_room[dj->rooms[dj->current_room].id].model, scene->shader, scene->camera, NULL);
        }
        else if (model && model->isRenderable) {
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


void physicsSystem(Scene* scene) {
    for (int i = 0; i < scene->numEntities; i++) {
        Entity* entity = &scene->entities[i];
        RigidBody* rigidBody = (RigidBody*)getComponent(entity, COMPONENT_RIGIDBODY);
        Collider* collider = (Collider*)getComponent(entity, COMPONENT_COLLIDER);

        if (collider && rigidBody) {
            // Handle collisions with other entities
            for (int j = 0; j < scene->numEntities; ++j) {
                if (i == j) continue;
                Entity* otherEntity = &scene->entities[j];
                Dungeon* dj = (Dungeon*)getComponent(otherEntity, COMPONENT_DUNGEON);
                Collider* otherCollider;
                if (dj) {  
                    otherCollider = (Collider*)dj->type_room[dj->rooms[dj->current_room].id].col;
                }
                else{
                    otherCollider = (Collider*)getComponent(otherEntity, COMPONENT_COLLIDER);
                }
                if (otherCollider) {
                    for (int k = 0; k < collider->numCollider; ++k) {
                        for (int l = 0; l < otherCollider->numCollider; ++l) {
                            if (glm_aabb_aabb(collider->boundingBox[k], otherCollider->boundingBox[l])) {
                                // Handle collision response here
                                // Example: Simple resolution by resetting velocity
                                glm_vec3_copy(((Model*)getComponent(entity,COMPONENT_RENDERABLE))->position,rigidBody->velocity );
                                break;
                            }
                        }
                    }
                }
            }
            // Update position based on velocity
            glm_vec3_copy(rigidBody->velocity, ((Model*)getComponent(entity,COMPONENT_RENDERABLE))->position);
        }
    }
}