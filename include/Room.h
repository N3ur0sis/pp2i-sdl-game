#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Model.h>
#include <Component.h>
typedef struct _Room Room;

struct  _Room
{
    int* data;
    int nb_door;
    int id;
    int type;

};
typedef struct _L_Room {
    Model* model;
    Model* col;
}L_Room;
void freeRoom(Room* room);
void freeLRoom(L_Room* l);
void initializeRoom(Room* room);
void initializeBossRoom(Room *room);
void initializeLootRoom(Room *room);
void initializeFightRoom(Room *room);

