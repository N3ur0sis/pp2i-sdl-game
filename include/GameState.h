#pragma once

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
    int g_WindowWidth;
    int g_WindowHeight;
    char* g_WindowTitle;
    int nextSceneIndex;
    bool change;
    // Add other game state variables as needed
} GameState;