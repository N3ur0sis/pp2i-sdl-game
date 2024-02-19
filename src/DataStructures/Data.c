//
// Created by Victor Davillé on 19/02/2024.
//

#include "Data.h"

void printData(union Data data) {
    if (data.i) {
        printf("%d\n", data.i);
    } else if (data.f) {
        printf("%f\n", data.f);
    } else {
        printf("%s\n", data.str);
    }
}
