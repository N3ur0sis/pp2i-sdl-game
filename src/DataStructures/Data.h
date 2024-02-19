//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_DATA_H
#define PP2I_DATA_H

#include <stdlib.h>
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

void printData(union Data data);

#endif //PP2I_DATA_H
