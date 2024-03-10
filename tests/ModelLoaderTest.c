//
// Created by Victor Davillé on 26/02/2024.
//
#include "ModelLoader.h"

int main(void) {
    Vector* vertices = createVector(VECTOR);
    Vector* normals = createVector(VECTOR);
    Vector* uvs = createVector(VECTOR);
    Vector* indices = createVector(VECTOR);
    ModelLoader("../ressources/teapot.obj", &vertices, &normals, &uvs, &indices);

    printVector(vertices);
    printVector(indices);

    return 0;
}
