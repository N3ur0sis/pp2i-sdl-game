#include "Room.h"




void freeRoom(Room* room){
    if (room==NULL){return;}
}


void freeLRoom(L_Room* l){
    if (l==NULL){return;}
    ModelFree(l->col);
    ModelFree(l->model);
}