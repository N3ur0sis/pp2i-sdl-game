#pragma once
#include <Inventory.h>

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
    Inventory* inventory;
    int g_WindowWidth;
    int g_WindowHeight;
    char* g_WindowTitle;
    bool isPlayerDead;
    int nextSceneIndex;
    int previousSceneIndex;
    bool change;
    bool isForestDungeonDone;
    int settingsNum;
    // Add other game state variables as needed
} GameState;