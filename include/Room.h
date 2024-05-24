#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Model.h>
#include <Component.h>
#define NB_ENEMY 5

typedef struct _Room Room;

struct  _Room
{
    int* data;
    int nb_door;
    int id;
    int type;
    bool isCompleted;
    int nb_enemy;
    int id_enemy[NB_ENEMY];

};
typedef struct _L_Room {
    Model* model;
    Collider* col;
}L_Room;
void freeRoom(Room* room);
void freeLRoom(L_Room* l);
void initializeRoom(Room* room);
void initializeBossRoom(Room *room);
void initializeLootRoom(Room *room);
void initializeFightRoom(Room *room);

