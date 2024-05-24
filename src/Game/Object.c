#include <Objects.h>

Object* Object_create(char* name, char* description, int id) {
    Object* object = (Object*)calloc(1, sizeof(Object));
    object->name = name;
    object->description = description;
    object->id = id;
    return object;
}




void printObject(int id, int nb) {
    printf("L'inventaire contient %d objects de type %d\n", nb, id);
}

char* checkIdObject(int id) {
    const int MAX_PATH_LENGTH = 256;
    char* path = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));

    switch (id) {
        case 0 :
            strcpy(path, "assets/images/Heart_Orange_1.png");
            break;
        case 1 : 
            strcpy(path, "assets/images/Heart_Blue_1.png");
            break;
        case 2 :
            strcpy(path, "assets/images/heart.png");
            break;
        default :
            strcpy(path, "assets/images/map.png");
            break;
    }
    return path;
}