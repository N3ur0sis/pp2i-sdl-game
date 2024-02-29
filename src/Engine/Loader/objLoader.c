#include <objLoader.h>




Obj loadObj(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return (Obj) {0};
    }
    char line[6536];
    int posIndex = 0;
    int numVertices = 0;
    int numIndices = 0;
    // Initialize vertices and indices arrays
    int size = 6536 * 6536;
    GLfloat* vertices = malloc(size * sizeof(GLfloat));
    GLuint* indices = malloc(size * sizeof(GLuint));
    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            // Handle vertices
            sscanf(line, "v %f %f %f", &vertices[posIndex], &vertices[posIndex+1], &vertices[posIndex+2]);
            posIndex += 3;
            numVertices +=1;
        } else if (line[0] == 'f' && line[1] == ' ') {
            // Handle faces
            char temp[3][128];
            sscanf(line, "f %s %s %s", temp[0], temp[1], temp[2]);
            for (int i = 0; i < 3; i++) {
                sscanf(temp[i], "%d/%d/%d", (int*)&indices[numIndices], (int*)&indices[numIndices+1], (int*)&indices[numIndices+2]);
                numIndices++;
            }
        }
    }
    fclose(file);
    // Allocate memory for the struct
    Obj mesh;
    mesh.vertices = malloc(numVertices * 3 * sizeof(GLfloat));
    mesh.indices = malloc(numIndices * 3 * sizeof(GLuint));
    mesh.numVertices = numVertices * 3;
    mesh.numIndices = numIndices;
    // Copy the data to the struct
    for (int i = 0; i < numVertices * 3; i++) {
        mesh.vertices[i] = (GLfloat)vertices[i];
    }
    for (int i = 0; i < numIndices * 3; i++) {
        mesh.indices[i] = indices[i] -1;
    }
    free(vertices);
    free(indices);
    return mesh;
}