#include <Menu.h>

void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram){
    SDL_Color color = {0, 0, 0, 255};
    SDL_Color gold = {255, 215, 0, 255};

    RenderText("MENU", color, gameState->g_WindowWidth / 2, 9 * gameState->g_WindowHeight / 10, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    if (gameState->settingsNum < 0){
        gameState->settingsNum = 1;
    } else if (gameState->settingsNum > 1){
        gameState->settingsNum = 0;
    }

    if (gameState->settingsNum == 0){
        RenderText("Resume", gold, gameState->g_WindowWidth / 2, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else {
        RenderText("Resume", color, gameState->g_WindowWidth / 2, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }

    if (gameState->settingsNum == 1){
        RenderText("Quit", gold, gameState->g_WindowWidth / 2, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else {
        RenderText("Quit", color, gameState->g_WindowWidth / 2, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }


    RenderImage("assets/images/Settings.png", gameState->g_WindowWidth / 2 , 9 * gameState->g_WindowHeight / 10 - 80, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    if (gameState->settingsNum == 0){
        RenderText("> ", gold, gameState->g_WindowWidth / 2 - 70, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else if (gameState->settingsNum == 1){
        RenderText("> ", gold, gameState->g_WindowWidth / 2 - 50, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }

}