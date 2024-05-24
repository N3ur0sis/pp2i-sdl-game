#include "Room.h"




void freeRoom(Room* room){
    if (room==NULL){return;}
}


void freeLRoom(L_Room* l){
    if (l==NULL){return;}
    FreeCollider(l->col);
    ModelFree(l->model);
}