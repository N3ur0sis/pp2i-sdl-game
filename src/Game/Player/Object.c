#include <Objects.h>

Object* Object_create(char* name, char* description, int id) {
    Object* object = (Object*)calloc(1, sizeof(Object));
    object->name = name;
    object->description = description;
    object->id = id;
    return object;
}


Object* Object_createFromId(int id) {
    char* name = nameFromId(id);
    char* description = descriptionFromId(id);
    int cost = costFromId(id);
    return Object_create(name, description, id);
}



void printObject(int id, int nb) {
    printf("L'inventaire contient %d objects de type %d\n", nb, id);
}

char* checkIdObject(int id) {
    const int MAX_PATH_LENGTH = 256;
    char* path = (char*)malloc(MAX_PATH_LENGTH * sizeof(char));

    switch (id) {
        case 1 :
            strcpy(path, "assets/images/Heart_Orange_1.png");
            break;
        case 2 : 
            strcpy(path, "assets/images/Heart_Blue_1.png");
            break;
        case 3 :
            strcpy(path, "assets/images/heart.png");
            break;
        default :
            strcpy(path, "assets/images/Hearts_Blue_1.png");
            break;
    }
    return path;
}


char* nameFromId(int id) {
    char* name = (char*)malloc(256 * sizeof(char));
    switch (id) {
        case 1 :
            strcpy(name, "Potion de vie");
            break;
        case 2 : 
            strcpy(name, "Épée");
            break;
        case 3 :
            strcpy(name, "Torche");
            break;
        case 4 :
            strcpy(name, "Bouclier");
            break;
        default :
            strcpy(name, "Objet inconnu");
            break;
    }
    return name;
}


char* descriptionFromId(int id) {
    char* description = (char*)malloc(256 * sizeof(char));
    switch (id) {
        case 1 :
            strcpy(description, "Restaure 10 points de vie");
            break;
        case 2 : 
            strcpy(description, "Permet de se défendre des monstres");
            break;
        case 3 :
            strcpy(description, "Eclaire dans le noir");
            break;
        case 4 :
            strcpy(description, "Protège des attaques");
            break;
        default :
            strcpy(description, "Objet inconnu");
            break;
    }
    return description;
}


int costFromId(int id) {
    switch (id) {
        case 1 :
            return 10;
        case 2 : 
            return 20;
        case 3 :
            return 5;
        case 4 :
            return 15;
        default :
            return 0;
    }
}