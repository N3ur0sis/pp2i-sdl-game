typedef struct _Object {
    char* name;
    char* description;
    int id;
} Object;




typedef struct _Inventory {
    Object* objects;
    int size;
    int capacity;
} Inventory;