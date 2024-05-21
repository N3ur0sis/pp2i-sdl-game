#pragma once

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
    int g_WindowWidth;
    int g_WindowHeight;
    char* g_WindowTitle;
    bool isPlayerDead;
    int nextSceneIndex;
    int previousSceneIndex;
    bool change;
    bool isForestDungeonDone;
    // Add other game state variables as needed
} GameState;