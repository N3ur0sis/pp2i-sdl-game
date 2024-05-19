#pragma once

typedef struct GameState {
    bool enemyIsAttacking;
    bool playerIsAttacking;
    float playerHealth;
    int g_WindowWidth;
    int g_WindowHeight;
    char* g_WindowTitle;
    // Add other game state variables as needed
} GameState;