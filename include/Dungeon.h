#pragma once
#include "Room.h"

#define nb_room_max 15;
#define nb_room_min 10;

typedef struct _Dungeon Dungeon;
struct  _Dungeon
{
    Room* rooms;
    
};


void initialize(Dungeon dj);
int getNumRoom(Dungeon dj);

