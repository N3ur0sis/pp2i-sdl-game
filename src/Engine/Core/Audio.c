/*
* @file Audio.c
* @brief Implementations of audio functions.
*/

#include <Audio.h>

/**
 * @brief Temporary audio implementation.
 * 
 * This function is a temporary implementation of audio.
 */
void TempAudioImpl(void){
        /* Music Player*/
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    Mix_Music *bgm = Mix_LoadMUS("assets/music/my-little-garden-of-eden-112845.mp3");
    if (bgm == NULL) {
    fprintf(stderr, "Failed to load background music: %s\n", Mix_GetError());
    return;
    }

    if (Mix_PlayMusic(bgm, -1) == -1) {  
    fprintf(stderr, "SDL_mixer could not play music! SDL_mixer Error: %s\n", Mix_GetError());
    return;
    }
    Mix_VolumeMusic(10); // 64=50% du volume
}