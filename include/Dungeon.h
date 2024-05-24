#pragma once

#include <Room.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "List.h"
#include <stdbool.h>
#include <string.h>
#include <GameState.h>
#include <Scene.h>

#define NB_ROOM_MAX 15
#define NB_ROOM_MIN 10
#define MIN_DOOR 1
#define MAX_DOOR 4
#define NB_MODEL_SALLE 8
#define ChangeTime 2000.0f
#define LootChance 3;
#define FightChance 2;

typedef struct _Dungeon Dungeon;
struct  _Dungeon
{
    Room* rooms;
    L_Room* type_room;
    char **adj;
    char direction;
    char previous_direction;
    int nb_rooms;
    int current_room;
    int previous_room;
    int nb_enemy;
    bool change;
    bool hasKey;
    bool quit;
    float lastRoomChangeTime;

    
};

Dungeon* dj_create();
void freeDungeon(Dungeon *dj);
void freeTypeRooms(Dungeon* dj);
void initialize(Dungeon *dj);
void initializeAdjacencyList(Dungeon *dj);
void freeAdjacencyList(Dungeon *dj);
void printAdjList(Dungeon *dj);
void initializeRooms(Dungeon *dj);
void freeRooms(Dungeon* dj);
void Affiche(Dungeon *dj);
int maxList(int list[], int size);
int max(int a, int b);
void depthFirstSearch(Dungeon *dj, int room, int depth, int *depths, int *visited);
int *profondeur(Dungeon *dj);
void printDepth(int *depths, int nb_rooms) ;
void LoadRoom(Scene* scene,Model* player, Dungeon* dj,RigidBody* body, Collider* collider,GameState* gameState);
void LoadRoom1C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom3C(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2I(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom3T(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2L(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom4C(Scene* scene,GameState* gameState,Model* player,Dungeon*dj,RigidBody* body);
void LoadRoomB(Scene* scene,GameState* gameState,Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LogicRoom1C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom2C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom3C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom4C (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom2L (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom2I (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoom3T (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void LogicRoomB (Scene* scene,GameState* gameState,Dungeon*dj,RigidBody* body );
void initializeLRooms(Dungeon *dj);
void setTypeRoom(Dungeon* dj);
void displayMiniMap(Scene* scene, Dungeon* dj,GameState* gameState);