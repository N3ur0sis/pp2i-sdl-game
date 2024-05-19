#pragma once

#include <stdlib.h>
#include "stdio.h"
typedef struct _List{
    int val;
    struct _List *next;
} List;

List *create_list(int val, List *next);
void free_list(List *Liste);
void printL(List *L);
int len(List*L);
void append(List **head, int value);
void removeLast(List **head);