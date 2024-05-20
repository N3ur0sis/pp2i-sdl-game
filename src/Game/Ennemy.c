#include "Ennemy.h"

Ennemy* createEnnemy(char * name){
    Ennemy * e = malloc(sizeof(Ennemy));
    e->name = name;
    return e;
}

