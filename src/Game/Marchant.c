#include <Marchant.h>

Entity* createMarchant(Scene* scene, vec3 position, vec3 scale, vec3 rotation) {
    Entity* marchantEntity = createEntity(scene);
    if (marchantEntity != NULL) {
        Model* marchant = (Model*)calloc(1, sizeof(Model));
        ModelCreate(marchant, "assets/models/start/marchang.obj");
        marchant->isRenderable = true;
        addComponent(marchantEntity, COMPONENT_RENDERABLE, marchant);

        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->position[0] = position[0];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->position[1] = position[1];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->position[2] = position[2];

        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->scale[0] = scale[0];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->scale[1] = scale[1];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->scale[2] = scale[2];

        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->rotation[0] = rotation[0];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->rotation[1] = rotation[1];
        ((Model*)getComponent(marchantEntity, COMPONENT_RENDERABLE))->rotation[2] = rotation[2]; 

        Collider* marchantCollision = ColliderCreate("assets/models/start/marchang.obj");
        glm_translate_make(marchantCollision->transformMatrix, position);
        UpdateCollider(marchantCollision);
        addComponent(marchantEntity, COMPONENT_COLLIDER, marchantCollision);
    }
    return marchantEntity;
}


void talkToMarchant(GameState* gameState, Scene* scene, int* click_counter, bool* is_clicking, bool* isBusy) {
    SDL_Color color_black = {0, 0, 0, 0};
    SDL_Color color_white = {255, 255, 255, 0};
    switch (*click_counter) {
    case 0:
        RenderText("   Marchant         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("Bien le bonjour, c'est une bonne journée", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("n'est ce pas ?", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 1:
        RenderText("   Marchant         ", color_white, gameState->g_WindowWidth / 2 - 175, gameState->g_WindowHeight / 15 + 200, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("Aurais tu quelques sous à m'échanger", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 140 , 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("contre des babioles ?", color_black, gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15 + 110, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderText("               Cliquez pour continuer...", color_black, gameState->g_WindowWidth / 2 + 45, gameState->g_WindowHeight / 15 + 50, 25, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        RenderImage("assets/images/dialog-box.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 15, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 2:
        RenderImage("assets/models/start/Inventory_Example_01.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 2, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter) = 0;
            *isBusy = false;
            *is_clicking = true;

        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
    default:
        break;
    }
}
