/*
* Menu.c
* Implementation of the pause menu.
* Authors: VD
*/

#include <Menu.h>

/**
 * @brief Draws the pause menu.
 * 
 * This function draws the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param shaderProgram Pointer to the shader program.
 */
void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram){
    SDL_Color color = {0, 0, 0, 255};
    SDL_Color gold = {255, 215, 0, 255};
    
    RenderText("MENU", color, gameState->g_WindowWidth / 2, 9 * gameState->g_WindowHeight / 10, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    if (gameState->settingsNum < 0){
        gameState->settingsNum = 2;
    } else if (gameState->settingsNum > 2){
        gameState->settingsNum = 0;
    }

    if (gameState->settingsNum == 0){
        RenderText("Resume", gold, gameState->g_WindowWidth / 2, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else {
        RenderText("Resume", color, gameState->g_WindowWidth / 2, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }

    if (gameState->settingsNum == 1){
        RenderText("Restart", gold, gameState->g_WindowWidth / 2, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else {
        RenderText("Restart", color, gameState->g_WindowWidth / 2, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }

    if (gameState->settingsNum == 2){
        RenderText("Quit", gold, gameState->g_WindowWidth / 2, 5 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else {
        RenderText("Quit", color, gameState->g_WindowWidth / 2, 5 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }


    RenderImage("assets/images/Settings.png", gameState->g_WindowWidth / 2 , 9 * gameState->g_WindowHeight / 10 - 80, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    if (gameState->settingsNum == 0){
        RenderText("> ", gold, gameState->g_WindowWidth / 2 - 70, 7 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else if (gameState->settingsNum == 1){
        RenderText("> ", gold, gameState->g_WindowWidth / 2 - 80, 6 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    } else if (gameState->settingsNum == 2){
        RenderText("> ", gold, gameState->g_WindowWidth / 2 - 50, 5 * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
    }

}