//
// Created by Victor Davillé on 19/02/2024.
//

#include "Data.h"

void printData(Data data) {
    if (data.i) {
        printf("%d\n", data.i);
    } else if (data.f) {
        printf("%f\n", data.f);
    } else if (!empty(data.vector)) {
        printVector(data.vector);
    } else {
        printf("%s\n", data.str);
    }
}
