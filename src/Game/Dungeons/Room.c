#include "Room.h"




void freeRoom(Room* room){
    if (room==NULL){return;}
    free(room);
}


void freeLRoom(L_Room* l){
    if (l==NULL){return;}
    FreeCollider(l->col);
    ModelFree(l->model);
    free(l);
}