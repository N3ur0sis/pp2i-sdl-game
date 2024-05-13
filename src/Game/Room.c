#include "Room.h"




void freeRoom(Room* room){
    if (room==NULL){return;}
    free(room->col);
    free(room->model);
}


