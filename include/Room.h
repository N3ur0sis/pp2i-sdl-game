#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Model.h>
#include <Player.h>
typedef struct _Room Room;

struct  _Room
{
    char* model;
    char* col;
    int* data;
    int nb_door;
    int id;

};

void freeRoom(Room* room);
void initializeRoom(Room* room);
void initializeBossRoom(Room *room);
void initializeLootRoom(Room *room);
void initializeFightRoom(Room *room);

