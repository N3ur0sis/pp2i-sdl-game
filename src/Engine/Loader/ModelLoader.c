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
            Vector* vertex = createVector();
            reserve(vertex, 3);
            float x, y, z;
            sscanf(line, "v %f %f %f", &x, &y, &z);
            Data data;
            data.f = x;
            push_back(vertex, data);
            data.f = y;
            push_back(vertex, data);
            data.f = z;
            push_back(vertex, data);
            push_back(*vertices, vertex);
        }
    }
}