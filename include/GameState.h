#pragma once
#include <Inventory.h>

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
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
    int settingsNum;
    bool restarting;
    // Add other game state variables as needed
} GameState;