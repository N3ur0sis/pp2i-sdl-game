//
// Created by Victor Davillé on 19/02/2024.
//

#include "../Vector.h"
#include <assert.h>

void createVectorTest() {
    Vector* vector = createVector();
    assert(vector != NULL);
    destroyVector(vector);
}

void sizeTest() {
    Vector* vector = createVector();
    assert(size(vector) == 0);
    union Data data;
    data.i = 1;
    push_back(vector, data);
    assert(size(vector) == 1);
    destroyVector(vector);
}

void capacityTest() {
    Vector* vector = createVector();
    assert(capacity(vector) == 10);
    union Data data;
    data.i = 1;
    push_back(vector, data);
    assert(capacity(vector) == 10);
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    assert(capacity(vector) == 20);
    destroyVector(vector);
}

void resizeTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    resize(vector, 5, data);
    assert(size(vector) == 5);
    assert(capacity(vector) == 10);
    destroyVector(vector);
}

void emptyTest() {
    Vector* vector = createVector();
    assert(empty(vector));
    union Data data;
    data.i = 1;
    push_back(vector, data);
    assert(!empty(vector));
    destroyVector(vector);
}

void reserveTest() {
    Vector* vector = createVector();
    reserve(vector, 20);
    assert(capacity(vector) == 20);
    destroyVector(vector);
}

void shrink_to_fitTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    push_back(vector, data);
    reserve(vector, 20);
    shrink_to_fit(vector);
    assert(capacity(vector) == 1);
    destroyVector(vector);
}

void operator_indexTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    push_back(vector, data);
    assert(operator_index(vector, 0).i == 1);
    destroyVector(vector);
}

void push_backTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    push_back(vector, data);
    assert(size(vector) == 1);
    assert(operator_index(vector, 0).i == 1);
    destroyVector(vector);
}

void pop_backTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    push_back(vector, data);
    pop_back(vector);
    assert(size(vector) == 0);
    destroyVector(vector);
}

void insertTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    insert(vector, 0, data);
    assert(size(vector) == 1);
    assert(operator_index(vector, 0).i == 1);
    data.i = 2;
    insert(vector, 0, data);
    assert(size(vector) == 2);
    assert(operator_index(vector, 0).i == 2);
    assert(operator_index(vector, 1).i == 1);
    data.i = 3;
    insert(vector, 20, data);
    printVector(vector);
    assert(size(vector) == 21);
    assert(operator_index(vector, 20).i == 3);
    destroyVector(vector);
}

void eraseTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    erase(vector, 0);
    assert(size(vector) == 9);
    assert(operator_index(vector, 0).i == 1);
    destroyVector(vector);
}

void clearTest() {
    Vector* vector = createVector();
    union Data data;
    data.i = 1;
    for (int i = 0; i < 10; i++) {
        push_back(vector, data);
    }
    clear(vector);
    assert(size(vector) == 0);
    destroyVector(vector);
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
    return 0;
}
