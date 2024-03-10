#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    float *vertices;
    float *uvs;
    int *indices;
    int numVertices;
    int numIndices;
    int numUvs;
} Obj;

Obj loadObj(const char *filename);