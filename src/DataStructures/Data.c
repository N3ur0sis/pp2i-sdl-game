//
// Created by Victor Davillé on 19/02/2024.
//

#include "Data.h"

Data* createIntData(int value) {
    Data* data = (Data*) malloc(sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    data->type = INT;
    data->value.i = value;
    return data;
}

Data* createFloatData(float value) {
    Data* data = (Data*) malloc(sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    data->type = FLOAT;
    data->value.f = value;
    return data;
}

Data* createStringData(char* value) {
    Data* data = (Data*) malloc(sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    data->type = STRING;
    strcpy(data->value.str, value);
    return data;
}

Data* createVectorData(Vector* value) {
    Data* data = (Data*) malloc(sizeof(Data));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    data->type = VECTOR;
    data->value.vector = value;
    return data;
}

void printData(Data* data) {
    if (data->type == INT) {
        printf("%d ", data->value.i);
    } else if (data->type == FLOAT) {
        printf("%f ", data->value.f);
    } else if (data->type == STRING) {
        printf("%s ", data->value.str);
    } else if (data->type == VECTOR) {
        printf("Vector: ");
        printVector(data->value.vector);
    } else {
        printf("Invalid type\n");
    }
}

void* getValue(Data* data) {
    if (data->type == INT) {
        return &data->value.i;
    } else if (data->type == FLOAT) {
        return &data->value.f;
    } else if (data->type == STRING) {
        return data->value.str;
    } else if (data->type == VECTOR) {
        return data->value.vector;
    } else {
        printf("Invalid type\n");
        return NULL;
    }
}

Type type(Data* data) {
    return data->type;
}

