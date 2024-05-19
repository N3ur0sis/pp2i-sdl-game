//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_DATA_H
#define PP2I_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Vector.h"
#include "Type.h"

typedef struct _Data Data;
typedef struct _Vector Vector;

struct _Data {
    Type type;
    union {
        int i;
        float f;
        char str[20];
        Vector* vector;
    } value;
};

Data* createIntData(int value);

Data* createFloatData(float value);

Data* createStringData(char* value);

Data* createVectorData(Vector* value);

bool equalsData(Data* data1, Data* data2);

void printData(Data* data);

void* getValue(Data* data);

Type type(Data* data);

#endif //PP2I_DATA_H
