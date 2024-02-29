#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    float *vertices;
    int *indices;
    int numVertices;
    int numIndices;
} Obj;

Obj loadObj(const char *filename);