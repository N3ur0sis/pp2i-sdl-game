#pragma once
#include <Model.h>



typedef struct _Room Room;

struct  _Room
{
    Model* room;
    int* data;
    int nb_door;

};

