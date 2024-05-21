#include "Engine.h"

Application* ApplicationCreate(int width, int height, const char* title){

    Application* app = (Application*)calloc(1, sizeof(Application));
    
    /* Initialize SDL and Create window */
    app->window = WindowCreate(width, height, title);
    if(!app->window){
        printf("Failed to create Window");
        return NULL;
    }
    
    /* Load OpenGL and initialize the engine */
    EngineInit();

    /* Initialize Engine Components */
    app->time = (Time*)calloc(1, sizeof(Time));
    app->event = (SDL_Event*)calloc(1, sizeof(SDL_Event));
    app->running = true;
    app->time->lastUpdate = SDL_GetTicks();
    app->time->nbFrames = 0;

    return app;
}

void EngineInit(void){

	/* Load Glad for current context */
    gladLoadGLLoader(SDL_GL_GetProcAddress);

	/* Basic renderign properties */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); /* Set the cleared back buffer to black */
    glCullFace(GL_BACK);                  /* Set back-face culling */
    glEnable(GL_CULL_FACE);               /* Enable use of back/front face culling */
    glEnable(GL_DEPTH_TEST);              /* Enable use of depth testing */
    glDisable(GL_STENCIL_TEST);           /* Disable stencil test for speed */
    glEnable(GL_MULTISAMPLE);  
    printf("%s", glGetString(GL_VERSION));
}

void EngineQuit(void) {
    
	SDL_Quit();
	exit(EXIT_SUCCESS);

}

void StartFrame(Application* game, GameState* gameState){

    /* Clearn screen for this new frame */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Per-frame time logic */
    game->time->currentUpdate = SDL_GetTicks();
    game->time->nbFrames++;
    if( game->time->currentUpdate - game->time->lastUpdate >= 1000.0f){
        printf("%d fps\n", game->time->nbFrames);
        game->time->nbFrames = 0;
        game->time->lastUpdate += 1000.0f;
    }
    //game->time->deltaTime = (game->time->currentUpdate - game->time->lastUpdate) / 1000.0f;
    /* Input Handling */
    while(SDL_PollEvent(game->event)){
        processInput(game->event, &game->running, gameState);
    }
}

void EndFrame(Application* game){

    SDL_GL_SwapWindow(game->window->m_window);
}
