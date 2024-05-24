#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _Object {
    char* name;
    char* description;
    int id;
} Object;



Object* Object_create(char* name, char* description, int id);
void printObject(int id, int nb);
char* checkIdObject(int id);