#pragma once
#include <Inventory.h>

typedef struct _Menu Menu;

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
    float max_health;
    Inventory* inventory;
    Inventory* marchantInventory;
    int g_WindowWidth;
    int g_WindowHeight;
    bool isPlayerDead;
    int nextSceneIndex;
    int currentSceneIndex;
    int previousSceneIndex;
    bool change;
    bool isForestDungeonDone;
    Menu* pauseMenu;
    bool restarting;
    bool mainMenuOpen;
    int money;
    bool fullscreen;
    // Add other game state variables as needed
} GameState;