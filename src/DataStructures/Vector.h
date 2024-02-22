//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_VECTOR_H
#define PP2I_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Data.h"

typedef struct _Vector Vector;
typedef union _Data Data;

struct _Vector {
    Data* data;
    int size;
    int capacity;
};

Vector* createVector();

int size(Vector* vector);

int capacity(Vector* vector);

void resize(Vector* vector, int size, Data data);

bool empty(Vector* vector);

void reserve(Vector* vector, int capacity);

void shrink_to_fit(Vector* vector);

Data operator_index(Vector* vector, int index);

void push_back(Vector* vector, Data data);

void pop_back(Vector* vector);

void insert(Vector* vector, int index, Data data);

void erase(Vector* vector, int index);

void clear(Vector* vector);

void printVector(Vector* vector);

void destroyVector(Vector* vector);

#endif //PP2I_VECTOR_H
