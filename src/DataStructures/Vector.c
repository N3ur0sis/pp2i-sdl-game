//
// Created by Victor Davillé on 19/02/2024.
//

#include "Vector.h"

Vector* createVector() {
    Vector* vector = (Vector*) malloc(sizeof(Vector));
    if (vector == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    vector->data = (Data*) malloc(10 * sizeof(Data));
    if (vector->data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    vector->size = 0;
    vector->capacity = 10;
    return vector;
}

int size(Vector* vector) {
    return vector->size;
}

int capacity(Vector* vector) {
    return vector->capacity;
}

void resize(Vector* vector, int size, Data data) {
    if (size > vector->capacity) {
        reserve(vector, size);
        if (vector->data == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    for (int i = vector->size; i < size; i++) {
        vector->data[i] = data;
    }
    vector->size = size;
}

bool empty(Vector* vector) {
    if (vector == NULL) {
        return true;
    }
    return vector->size == 0;
}

void reserve(Vector* vector, int capacity) {
    if (capacity > vector->capacity) {
        vector->data = (Data*) realloc(vector->data, capacity * sizeof(Data));
        if (vector->data == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        vector->capacity = capacity;
    }
}

void shrink_to_fit(Vector* vector) {
    vector->data = (Data*) realloc(vector->data, vector->size * sizeof(Data));
    vector->capacity = vector->size;
}

Data operator_index(Vector* vector, int index) {
    if (index < 0 || index >= vector->size) {
        printf("Index out of range\n");
        exit(1);
    }
    return vector->data[index];
}

void push_back(Vector* vector, Data data) {
    if (vector == NULL) {
        vector = createVector();
    }
    if (vector->size == vector->capacity) {
        reserve(vector, vector->capacity * 2);
    }
    vector->data[vector->size] = data;
    vector->size++;
}

void pop_back(Vector* vector) {
    if (vector == NULL || vector->size == 0) {
        printf("Vector is empty\n");
        return;
    }
    vector->size--;
}

void insert(Vector* vector, int index, Data data) {
    if (vector->size == vector->capacity) {
        reserve(vector, vector->capacity * 2);
    }
    if (index < 0) {
        index = 0;
    }
    if (index > vector->size) {
        resize(vector, index + 1, (Data) {0});
        vector->data[index] = data;
    } else {
        for (int i = vector->size; i > index; i--) {
            vector->data[i] = vector->data[i - 1];
        }
        vector->data[index] = data;
        vector->size++;
    }
}

void erase(Vector* vector, int index) {
    if (index < 0 || index >= vector->size) {
        printf("Index out of range\n");
        exit(1);
    }
    for (int i = index; i < vector->size - 1; i++) {
        vector->data[i] = vector->data[i + 1];
    }
    vector->size--;
}

void clear(Vector* vector) {
    vector->size = 0;
}

void printVector(Vector* vector) {
    for (int i = 0; i < vector->size; i++) {
        printData(vector->data[i]);
    }
}

void destroyVector(Vector* vector) {
    if (vector == NULL) {
        return;
    }
    free(vector->data);
    vector->data = NULL;
    free(vector);
}
