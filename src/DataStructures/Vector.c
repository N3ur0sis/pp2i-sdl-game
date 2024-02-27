//
// Created by Victor Davillé on 19/02/2024.
//

#include "Vector.h"

Vector* createVector(Type type) {
    Vector* vector = (Vector*) malloc(sizeof(Vector));
    if (vector == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    vector->data = (Data**) malloc(10 * sizeof(Data*));
    if (vector->data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    vector->size = 0;
    vector->capacity = 10;
    vector->type = type;
    return vector;
}

int size(Vector* vector) {
    return vector->size;
}

int capacity(Vector* vector) {
    return vector->capacity;
}

void resize(Vector* vector, int size, Data* data) {
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
        vector->data = (Data**) realloc(vector->data, capacity * sizeof(Data*));
        if (vector->data == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        vector->capacity = capacity;
    }
}

void shrink_to_fit(Vector* vector) {
    vector->data = (Data**) realloc(vector->data, vector->size * sizeof(Data*));
    vector->capacity = vector->size;
}

Data* operator_index(Vector* vector, int index) {
    if (index < 0 || index >= vector->size) {
        printf("Index out of range\n");
        exit(1);
    }
    return vector->data[index];
}

void push_back(Vector* vector, Data* data) {
    if (vector == NULL) {
        printf("Vector is NULL\n");
        exit(1);
    }
    if (vector->type != data->type) {
        printf("Invalid type\n");
        exit(1);
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

void insert(Vector* vector, int index, Data* data) {
    if (vector == NULL) {
        printf("Vector is NULL\n");
        exit(1);
    }
    if (vector->type != data->type) {
        printf("Invalid type\n");
        exit(1);
    }
    if (vector->size == vector->capacity) {
        reserve(vector, vector->capacity * 2);
    }
    if (index < 0) {
        index = 0;
    }
    if (index > vector->size) {
        resize(vector, index + 1, NULL);
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

bool equalsVector(Vector* vector1, Vector* vector2) {
    if (vector1->size != vector2->size) {
        return false;
    }
    for (int i = 0; i < vector1->size; i++) {
        if (!equalsData(vector1->data[i], vector2->data[i])) {
            return false;
        }
    }
    return true;
}

void printVector(Vector* vector) {
    for (int i = 0; i < vector->size; i++) {
        printData(vector->data[i]);
    }
    printf("\n");
}

int numElements(Vector* vector) {
    if (vector->type != VECTOR) {
        return vector->size;
    }
    int sum = 0;
    for (int i = 0; i < vector->size; i++) {
        sum += numElements(vector->data[i]->value.vector);
    }
    return sum;
}

GLfloat* toVertices(Vector* vector) {
if (vector->type != VECTOR) {
        return NULL;
    }
    GLfloat* vertices = (GLfloat*) malloc(numElements(vector) * sizeof(GLfloat));
    int index = 0;
    for (int i = 0; i < vector->size; i++) {
        Vector* vertex = vector->data[i]->value.vector;
        for (int j = 0; j < vertex->size; j++) {
            vertices[index] = (GLfloat) vertex->data[j]->value.f;
            index++;
        }
    }
    return vertices;
}

GLuint* toIndices(Vector* vector) {
    if (vector->type != VECTOR) {
        return NULL;
    }
    GLuint* indices = (GLuint*) malloc(numElements(vector) * sizeof(GLuint));
    int index = 0;
    for (int i = 0; i < vector->size; i++) {
        Vector* vertexIndex = vector->data[i]->value.vector;
        for (int j = 0; j < vertexIndex->size; j++) {
            indices[index] = (GLuint) vertexIndex->data[j]->value.i;
            index++;
        }
    }
    return indices;
}

void destroyVector(Vector* vector) {
    if (vector == NULL) {
        return;
    }
    free(vector->data);
    vector->data = NULL;
    free(vector);
}
