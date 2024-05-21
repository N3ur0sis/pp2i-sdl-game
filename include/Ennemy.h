#pragma once
#include <Model.h>
#include <Animator.h>

typedef struct _Ennemy {
    Model* model;
    char *name;
    Animator** animations;
}Ennemy;