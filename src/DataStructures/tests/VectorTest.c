//
// Created by Victor Davillé on 19/02/2024.
//

#include "../Vector.h"
#include <assert.h>

void createVectorTest() {
    Vector* vector = createVector(INT);
    assert(vector != NULL);
    destroyVector(vector);
}

void sizeTest() {
    Vector* vector = createVector(INT);
    assert(size(vector) == 0);
    Data* data = createIntData(1);
    push_back(vector, data);
    assert(size(vector) == 1);
    destroyVector(vector);
}

void capacityTest() {
    Vector* vector = createVector(INT);
    assert(capacity(vector) == 10);
    Data* data = createIntData(1);
    push_back(vector, data);
    assert(capacity(vector) == 10);
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    assert(capacity(vector) == 20);
    destroyVector(vector);
}

void resizeTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    resize(vector, 5, data);
    assert(size(vector) == 5);
    assert(capacity(vector) == 10);
    destroyVector(vector);
}

void emptyTest() {
    Vector* vector = createVector(INT);
    assert(empty(vector));
    Data* data = createIntData(1);
    push_back(vector, data);
    assert(!empty(vector));
    destroyVector(vector);
}

void reserveTest() {
    Vector* vector = createVector(INT);
    reserve(vector, 20);
    assert(capacity(vector) == 20);
    destroyVector(vector);
}

void shrink_to_fitTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    push_back(vector, data);
    reserve(vector, 20);
    shrink_to_fit(vector);
    assert(capacity(vector) == 1);
    destroyVector(vector);
}

void operator_indexTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    push_back(vector, data);
    assert(*((int*) getValue(operator_index(vector, 0))) == 1);
    destroyVector(vector);
}

void push_backTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    push_back(vector, data);
    assert(size(vector) == 1);
    assert(*((int*) getValue(operator_index(vector, 0))) == 1);
    destroyVector(vector);
}

void pop_backTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    push_back(vector, data);
    pop_back(vector);
    assert(size(vector) == 0);
    destroyVector(vector);
}

void insertTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    insert(vector, 0, data);
    assert(size(vector) == 1);
    assert(*((int*) getValue(operator_index(vector, 0))) == 1);
    data = createIntData(2);
    insert(vector, 0, data);
    assert(size(vector) == 2);
    assert(*((int*) getValue(operator_index(vector, 0))) == 2);
    assert(*((int*) getValue(operator_index(vector, 1))) == 1);
    data = createIntData(3);
    insert(vector, 20, data);
    assert(size(vector) == 21);
    assert(*((int*) getValue(operator_index(vector, 20))) == 3);
    destroyVector(vector);
}

void eraseTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    erase(vector, 0);
    assert(size(vector) == 9);
    assert(*((int*) getValue(operator_index(vector, 0))) == 1);
    destroyVector(vector);
}

void clearTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    clear(vector);
    assert(size(vector) == 0);
    destroyVector(vector);
}

void printVectorTest() {
    Vector* vector = createVector(INT);
    Data* data = createIntData(1);
    push_back(vector, data);
    printVector(vector);

    float f = 1.5;
    data = createFloatData(f);
    vector = createVector(FLOAT);
    push_back(vector, data);
    printVector(vector);

    char* str = "Hello";
    data = createStringData(str);
    vector = createVector(STRING);
    push_back(vector, data);
    printVector(vector);

    vector = createVector(VECTOR);
    Vector *vector2 = createVector(INT);
    Vector *vector3 = createVector(INT);
    push_back(vector2, createIntData(1));
    push_back(vector2, createIntData(2));
    push_back(vector3, createIntData(3));
    push_back(vector3, createIntData(4));
    push_back(vector, createVectorData(vector2));
    push_back(vector, createVectorData(vector3));
    printVector(vector);

    destroyVector(vector);
}

void equalsVectorTest() {
    Vector* vector1 = createVector(INT);
    Vector* vector2 = createVector(INT);
    assert(equalsVector(vector1, vector2));
    Data* data = createIntData(1);
    push_back(vector1, data);
    assert(!equalsVector(vector1, vector2));
    push_back(vector2, data);
    assert(equalsVector(vector1, vector2));
    destroyVector(vector1);
    destroyVector(vector2);

    vector1 = createVector(VECTOR);
    vector2 = createVector(VECTOR);
    Vector *vector3 = createVector(INT);
    Vector *vector4 = createVector(INT);
    push_back(vector3, createIntData(1));
    push_back(vector3, createIntData(2));
    push_back(vector4, createIntData(3));
    push_back(vector4, createIntData(4));
    push_back(vector1, createVectorData(vector3));
    push_back(vector1, createVectorData(vector4));
    push_back(vector2, createVectorData(vector3));
    push_back(vector2, createVectorData(vector4));
    assert(equalsVector(vector1, vector2));
    destroyVector(vector1);
    destroyVector(vector2);
}

int main(void) {
    createVectorTest();
    sizeTest();
    capacityTest();
    resizeTest();
    emptyTest();
    reserveTest();
    shrink_to_fitTest();
    operator_indexTest();
    push_backTest();
    pop_backTest();
    insertTest();
    eraseTest();
    clearTest();
    printVectorTest();
    return 0;
}
