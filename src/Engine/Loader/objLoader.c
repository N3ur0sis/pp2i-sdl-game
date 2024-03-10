#include <objLoader.h>

Obj loadObj(const char *filename) {

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return (Obj) {0};
    }
    char line[200];

    int posIndex = 0;
    int posUvs = 0;
    int numVertices = 0;
    int numIndices = 0;
    int numUvs = 0;

    // Initialize vertices and indices arrays
    int size = 20000;
    GLfloat* vertices = malloc(size * sizeof(GLfloat));
    GLfloat* uvs = malloc(size * sizeof(GLfloat));
    GLuint* posIndices = malloc(size * sizeof(GLuint));
    GLuint* texIndices = malloc(size * sizeof(GLuint));
    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            // Handle vertices
            sscanf(line, "v %f %f %f", &vertices[posIndex], &vertices[posIndex+1], &vertices[posIndex+2]);
            posIndex += 3;
            numVertices +=1;
        } else if (line[0] == 'v' && line[1] == 't') {
            // Handle vertices
            sscanf(line, "vt %f %f", &uvs[posUvs], &uvs[posUvs+1]);
            posUvs += 2;
            numUvs +=1;
        }else if (line[0] == 'f' && line[1] == ' ') {
            // Handle faces
            char temp[3][128];
            sscanf(line, "f %s %s %s", temp[0], temp[1], temp[2]);
            for (int i = 0; i < 3; i++) {
                int vInd,uvInd;
                sscanf(temp[i], "%d/%d", (int*)&vInd, (int*)&uvInd);
                texIndices[numIndices] = uvInd -1;
                posIndices[numIndices] = vInd - 1;
                numIndices++;
            }
        }
    }
    fclose(file);
    // Allocate memory for the struct
    Obj mesh;
    mesh.vertices = malloc(numIndices * 3 * sizeof(GLfloat));
    mesh.indices = malloc(numIndices * sizeof(GLuint));
    mesh.uvs = malloc(numIndices * 2 * sizeof(GLfloat));
    mesh.numVertices = numVertices;
    mesh.numIndices = numIndices;

    for (int i = 0; i < numIndices; i++) {
        mesh.indices[i] = i - 1;
    }
    // Copy the data to the struct
    for (int i = 0; i < numIndices; i++) {
        mesh.vertices[i * 3] = (GLfloat)vertices[posIndices[i] * 3];
        mesh.vertices[i * 3 + 1] = (GLfloat)vertices[posIndices[i] * 3 + 1];
        mesh.vertices[i * 3 + 2] = (GLfloat)vertices[posIndices[i] * 3 + 2];
    }

    for (int i = 0; i < numIndices; i++) {
        mesh.uvs[i * 2] = (GLfloat)uvs[texIndices[i] * 2];
        mesh.uvs[i * 2 + 1] = (GLfloat)uvs[texIndices[i] * 2 + 1];
    }





    free(vertices);
    free(uvs);
    free(posIndices);
    free(texIndices);
    return mesh;
}