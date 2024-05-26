/*
* Menu.c
* Implementation of the pause menu.
* Authors: VD
*/

#include <Menu.h>

/**
 * @brief Initializes the pause menu.
 * 
 * This function initializes the pause menu.
 * 
 */
Menu* MenuPauseInit(Application* game){
    Menu* menu = malloc(sizeof(Menu));
    menu->title = "Menu";
    char* options[6] = {"Resume", "Restart", "Save", "Load", "Settings", "Quit"};
    menu->options = malloc(6 * sizeof(char*));
    for (int i = 0; i < 6; i++){
        menu->options[i] = options[i];
    }
    menu->numOptions = 6;
    menu->selectedOption = 0;
    menu->parentMenu = NULL;
    menu->isSettings = false;
    menu->game = game;

    Menu* settingsMenu = malloc(sizeof(Menu));
    settingsMenu->title = "Settings";
    char* settingsOptions[2] = {"Fullscreen", "Back"};
    settingsMenu->options = malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++){
        settingsMenu->options[i] = settingsOptions[i];
    }
    settingsMenu->numOptions = 2;
    settingsMenu->selectedOption = 0;
    settingsMenu->parentMenu = menu;
    settingsMenu->isSettings = true;
    settingsMenu->game = game;

    menu->SettingsMenu = settingsMenu;

    return menu;
}

/**
 * @brief Updates the pause menu.
 * 
 * This function updates the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param menu Pointer to the menu.
 */
void MenuPauseReset(Menu* menu){
    menu->selectedOption = 0;
    menu->SettingsMenu->selectedOption = 0;
    menu->isSettings = false;
}

/**
 * @brief Moves the selection up in the pause menu.
 * 
 * This function moves the selection up in the pause menu.
 * 
 * @param menu Pointer to the menu.
 */
void MenuPauseUp(Menu* menu){
    if (menu->isSettings){
        menu->SettingsMenu->selectedOption--;
        if (menu->SettingsMenu->selectedOption < 0){
            menu->SettingsMenu->selectedOption = menu->SettingsMenu->numOptions - 1;
        }
    } else {
        menu->selectedOption--;
        if (menu->selectedOption < 0){
            menu->selectedOption = menu->numOptions - 1;
        }
    }
}

/**
 * @brief Moves the selection down in the pause menu.
 * 
 * This function moves the selection down in the pause menu.
 * 
 * @param menu Pointer to the menu.
 */
void MenuPauseDown(Menu* menu){
    if (menu->isSettings){
        menu->SettingsMenu->selectedOption++;
        if (menu->SettingsMenu->selectedOption >= menu->SettingsMenu->numOptions){
            menu->SettingsMenu->selectedOption = 0;
        }
    } else {
        menu->selectedOption++;
        if (menu->selectedOption >= menu->numOptions){
            menu->selectedOption = 0;
        }
    }
}

/**
 * @brief Selects an option in the pause menu.
 * 
 * This function selects an option in the pause menu.
 * 
 * @param menu Pointer to the menu.
 * @param gameState Pointer to the game state.
 * @param running Pointer to the running state flag.
 * @param isPaused Pointer to the paused state flag.
 */
void MenuPauseSelect(Menu* menu, GameState* gameState, bool* running, bool* isPaused){
    if (menu->isSettings){
        if (menu->SettingsMenu->selectedOption == 0){
            gameState->fullscreen = !gameState->fullscreen;
            if (SDL_SetWindowFullscreen(menu->game->window->m_window, gameState->fullscreen ? SDL_WINDOW_FULLSCREEN : 0) != 0) {
                fprintf(stderr, "Error toggling fullscreen: %s\n", SDL_GetError());
            } else {
                int w, h;
                SDL_GetWindowSize(menu->game->window, &w, &h);
                gameState->g_WindowWidth = w;
                gameState->g_WindowHeight = h;
            }

        } else if (menu->SettingsMenu->selectedOption == 1){
            menu->isSettings = false;
        }
        return;
    }
    if (menu->selectedOption == 0){
        *isPaused = false;
        menu->selectedOption = 0;
    } else if (menu->selectedOption == 1){
        gameState->isPlayerDead = true;
        *isPaused = false;
        setKeyState(SDLK_r, 1);
        gameState->restarting = true;
    } else if (menu->selectedOption == 2){
        // Save game
    } else if (menu->selectedOption == 3){
        // Load game
    } else if (menu->selectedOption == 4){
        menu->isSettings = true;
    } else if (menu->selectedOption == 5){
        *running = false;
    }
}

/**
 * @brief Draws the pause menu.
 * 
 * This function draws the pause menu.
 * 
 * @param game Pointer to the application.
 * @param gameState Pointer to the game state.
 * @param shaderProgram Pointer to the shader program.
 * @param menu Pointer to the menu.
 */
void MenuPauseDraw(Application* game, GameState* gameState, Shader* shaderProgram, Menu* menu){
    SDL_Color color = {0, 0, 0, 0};
    SDL_Color gold = {255, 215, 0, 0};
    //RenderText(menu->title, color, gameState->g_WindowWidth / 2, 9 * gameState->g_WindowHeight / 10, 50, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

    if (menu->isSettings){
        for (int i = 0; i < menu->SettingsMenu->numOptions; i++){
            if (i == menu->SettingsMenu->selectedOption){
                char* selectedOption = malloc(strlen(menu->SettingsMenu->options[i]) + 4);
                strcpy(selectedOption, "> ");
                strcat(selectedOption, menu->SettingsMenu->options[i]);
                RenderText(selectedOption, gold, gameState->g_WindowWidth / 2, (7 - i) * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
            } else {
                RenderText(menu->SettingsMenu->options[i], color, gameState->g_WindowWidth / 2, (7 - i) * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
            }
        }
    } else {
        for (int i = 0; i < menu->numOptions; i++){
            if (i == menu->selectedOption){
                char* selectedOption = malloc(strlen(menu->options[i]) + 4);
                strcpy(selectedOption, "> ");
                strcat(selectedOption, menu->options[i]);
                RenderText(selectedOption, gold, gameState->g_WindowWidth / 2, (7 - i) * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
            } else {
                RenderText(menu->options[i], color, gameState->g_WindowWidth / 2, (7 - i) * gameState->g_WindowHeight / 10, 30, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);
            }
        }
    }

    RenderImage("assets/images/Settings.png", gameState->g_WindowWidth / 2 , 9 * gameState->g_WindowHeight / 10 - 80, gameState->g_WindowWidth, gameState->g_WindowHeight, shaderProgram->m_program);

}