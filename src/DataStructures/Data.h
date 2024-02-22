//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_DATA_H
#define PP2I_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

typedef union _Data Data;
typedef struct _Vector Vector;

union _Data {
    int i;
    float f;
    char str[20];
    Vector* vector;
};

void printData(Data data);

#endif //PP2I_DATA_H
