//
// Created by Victor Davillé on 20/02/2024.
//

#include "ModelLoader.h"

bool ModelLoader(char* path, Vector** vertices, Vector** normals, Vector** uvs, Vector** vertexIndices) {
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
        } else if (line[0] == 'v' && line[1] == 'n') {
            Vector* normal = createVector(FLOAT);
            reserve(normal, 3);
            float x, y, z;
            sscanf(line, "vn %f %f %f", &x, &y, &z);
            Data* data = createFloatData(x);
            push_back(normal, data);
            data = createFloatData(y);
            push_back(normal, data);
            data = createFloatData(z);
            push_back(normal, data);
            push_back(*normals, createVectorData(normal));
        } else if (line[0] == 'v' && line[1] == 't') {
            Vector* uv = createVector(FLOAT);
            reserve(uv, 2);
            float x, y;
            sscanf(line, "vt %f %f", &x, &y);
            Data* data = createFloatData(x);
            push_back(uv, data);
            data = createFloatData(y);
            push_back(uv, data);
            push_back(*uvs, createVectorData(uv));
        } else if (line[0] == 'f') {
            Vector* vertexIndex = createVector(INT);
            reserve(vertexIndex, 3);
            int v1, v2, v3;
            sscanf(line, "f %d %d %d", &v1, &v2, &v3);
            Data* data = createIntData(v1);
            push_back(vertexIndex, data);
            data = createIntData(v2);
            push_back(vertexIndex, data);
            data = createIntData(v3);
            push_back(vertexIndex, data);
            push_back(*vertexIndices, createVectorData(vertexIndex));
        }
    }
    fclose(f);
    return true;
}
