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