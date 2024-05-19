#pragma once

#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "List.h"
#include <stdbool.h>
#include <string.h>
#include <GameState.h>

#define NB_ROOM_MAX 15
#define NB_ROOM_MIN 10
#define MIN_DOOR 1
#define MAX_DOOR 4
#define NB_MODEL_SALLE 8
#define ChangeTime 2000.0f
typedef struct _Dungeon Dungeon;
struct  _Dungeon
{
    Room* rooms;
    char **adj;
    int nb_rooms;
    char direction;
    int current_room;
    bool change;
    L_Room* type_room;
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
void LoadRoom(Model* player, Dungeon* dj,RigidBody* body, Collider* collider,GameState* gameState);
void LoadRoom1C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom3C(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2I(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom3T(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom2L(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LoadRoom4C(Model* player,Dungeon*dj,RigidBody* body);
void LoadRoomB(Model* map,Collider* col, Model* player,Dungeon *dj,RigidBody* body);
void LogicRoom1C (Dungeon* dj, RigidBody* body);
void LogicRoom2C (Dungeon* dj, RigidBody* body);
void LogicRoom3C (Dungeon* dj, RigidBody* body);
void LogicRoom4C (Dungeon* dj, RigidBody* body);
void LogicRoom2L (Dungeon* dj, RigidBody* body);
void LogicRoom2I (Dungeon* dj, RigidBody* body);
void LogicRoom3T (Dungeon* dj, RigidBody* body);
void LogicRoomB (Dungeon* dj, RigidBody* body);
void initializeLRooms(Dungeon *dj);