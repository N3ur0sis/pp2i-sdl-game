#include <Menu.h>

void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram){
    SDL_Color color = {0, 0, 0, 255};

    RenderText("MENU", color, gameState->g_WindowWidth / 2, 9 * gameState->g_WindowHeight / 10, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    RenderText("Resume", color, gameState->g_WindowWidth / 2, 7 * gameState->g_WindowHeight / 5, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    RenderImage("assets/images/Settings.png", gameState->g_WindowWidth / 2 - 100, 7 * gameState->g_WindowHeight / 5, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

}