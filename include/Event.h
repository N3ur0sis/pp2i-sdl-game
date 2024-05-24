#pragma once
#include <SceneManager.h>

#define CHANGE_SCENE_EVENT (SDL_USEREVENT + 1)

void HandleChangeScene(SceneManager* sceneManager);
void ChangeSceneEvent(int nextSceneIndex);