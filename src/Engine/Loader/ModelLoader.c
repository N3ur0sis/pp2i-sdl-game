//
// Created by Victor Davillé on 20/02/2024.
//

#include "ModelLoader.h"

bool ModelLoader(char* path, Vector** vertices, Vector** normals, Vector** uvs, Vector** indices) {
    FILE* f = fopen(path, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return false;
    }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == 'v' && line[1] == ' ') {
            Vector* vertex = createVector(FLOAT);
            reserve(vertex, 3);
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            Data* data = createFloatData(x);
            push_back(vertex, data);
            data = createFloatData(y);
            push_back(vertex, data);
            data = createFloatData(z);
            push_back(vertex, data);
            push_back(*vertices, createVectorData(vertex));
        }
    }
    normals[0] = createVector(FLOAT);
    uvs[0] = createVector(FLOAT);
    indices[0] = createVector(INT);
    fclose(f);
    return true;
}
