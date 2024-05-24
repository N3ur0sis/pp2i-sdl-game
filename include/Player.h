#pragma once
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <SceneManager.h>
#define DAMAGE 50.0f
#define ATTACK_RANGE 2.5f
void lerp_vec3(vec3 a, vec3 b, vec3 res, float t);
void playerMovement(Entity* player, float deltaTime, Camera* camera, Model* enemy);
void moveCameraPlayer(Camera* camera, vec3 position, vec3 targetPosition, float deltaTime);
float lerp_float(float a, float b, float t);
void lerp_camera(Camera* camera, vec3 old_pos, vec3 new_pos, float old_yaw, float new_yaw, int steps, float duration);
bool playerInteract();
void checkDead(GameState* gamestate);
void damagePlayer(GameState* gamestate, int damage);Entity* create_player(Scene*  scene,float x,float y,float z);
Entity* create_sword(Scene* scene,Entity* parent);
void player_attack(Entity* player,Entity* enemy,GameState* gameState);