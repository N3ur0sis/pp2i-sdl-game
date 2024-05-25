#pragma once

#include <Model.h>
#include <Animator.h>
#include <Entity.h>
#include <Scene.h>

typedef struct _EnemyComponent {
    vec3 direction;
    float detectionRange;
    float attackRange;
    float movementSpeed;
    float attackDamage;
    bool isAttacking;
    bool isAlive;
    float health;
    bool takeDamage;
} EnemyComponent;

Entity *create_golem(Scene* scene,float x,float y,float z,float scale);
Entity* create_golemPurple(Scene* scene,float x,float y,float z,float scale);
void golemLogic(Scene* scene,GameState* gameState,Entity* golem,Entity* player);
void updateEnemy(Entity* enemy, Entity* player, Scene* scene, GameState* gameState, float deltaTime);
void initializeEnemyComponent(Entity* enemy, float detectionRange, float attackRange, float movementSpeed, float attackDamage);