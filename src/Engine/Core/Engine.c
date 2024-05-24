/**
 * @file Engine.c
 * @brief Implementations of application functions.
 * @author Aymeric ROBERT
 */

#include <Engine.h>

/**
 * @brief Creates a new Application instance.
 * 
 * @param width The width of the application window.
 * @param height The height of the application window.
 * @param title The title of the application window.
 * @return Pointer to the created Application instance or NULL on failure.
 */
Application* ApplicationCreate(int width, int height, const char* title) {
    Application* app = (Application*)calloc(1, sizeof(Application));
    if (!app) {
        fprintf(stderr, "Failed to allocate memory for Application.\n");
        return NULL;
    }
    
    /* Initialize SDL and create window */
    app->window = WindowCreate(width, height, title);
    if (!app->window) {
        fprintf(stderr, "Failed to create Window.\n");
        free(app);
        return NULL;
    }
    
    /* Load OpenGL and initialize the engine */
    if (!EngineInit()) {
        fprintf(stderr, "Failed to initialize the engine.\n");
        WindowDelete(app->window);
        free(app);
        return NULL;
    }

    /* Initialize Engine Components */
    app->time = (Time*)calloc(1, sizeof(Time));
    app->event = (SDL_Event*)calloc(1, sizeof(SDL_Event));
    if (!app->time || !app->event) {
        fprintf(stderr, "Failed to allocate memory for Engine components.\n");
        free(app->time);
        free(app->event);
        WindowDelete(app->window);
        free(app);
        return NULL;
    }
    
    app->running = true;
    app->time->lastUpdate = SDL_GetTicks();
    app->time->nbFrames = 0;

    return app;
}

/**
 * @brief Initializes the game engine.
 * 
 * @return true if the engine was initialized successfully, false otherwise.
 */
bool EngineInit(void) {
    /* Load Glad for the current context */
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD.\n");
        return false;
    }

    /* Set basic rendering properties */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  /* Set the cleared back buffer to black */
    glCullFace(GL_BACK);                   /* Set back-face culling */
    glEnable(GL_CULL_FACE);                /* Enable back-face culling */
    glEnable(GL_DEPTH_TEST);               /* Enable depth testing */
    glDisable(GL_STENCIL_TEST);            /* Disable stencil testing for speed */
    glEnable(GL_MULTISAMPLE);              /* Enable multisampling for anti-aliasing */

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    if (TTF_Init() == -1) {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

/**
 * @brief Shuts down the game engine and exits the application.
 */
void EngineQuit(void) {
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


/**
 * @brief Starts a new frame in the application.
 * 
 * This function should be called at the beginning of each frame to process input and update the game state.
 * 
 * @param game Pointer to the Application instance.
 * @param gameState Pointer to the current game state.
 * @param sceneManager Pointer to the scene manager, can be NULL.
 */
void StartFrame(Application* game, GameState* gameState, SceneManager* sceneManager) {
    /* Clear the screen for this new frame */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Per-frame time logic */
    game->time->currentUpdate = SDL_GetTicks();
    if (sceneManager) {
        sceneManager->scenes[sceneManager->currentSceneIndex]->deltaTime = (game->time->currentUpdate - game->time->lastUpdate) / 1000.0f;
    }
    game->time->nbFrames++;
    if (game->time->currentUpdate - game->time->lastUpdate >= 1000.0f) {
        printf("FPS: %d\n", game->time->nbFrames);
        game->time->nbFrames = 0;
        game->time->lastUpdate += 1000.0f;
    }

    /* Input Handling */
    while (SDL_PollEvent(game->event)) {
        if (sceneManager){
            processInput(game->event, &game->running, gameState, sceneManager);
        }else{
            processInput(game->event, &game->running, gameState, NULL);
        }
    }
}

/**
 * @brief Ends the current frame in the application.
 * 
 * This function should be called at the end of each frame to render the scene and present the frame.
 * 
 * @param game Pointer to the Application instance.
 */
void EndFrame(Application* game) {
    game->time->lastUpdate = game->time->currentUpdate;
    SDL_GL_SwapWindow(game->window->m_window);
}