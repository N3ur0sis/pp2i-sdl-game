#include <Objects.h>



typedef struct _Inventory {
    Object* objects;
    int size;
    int capacity;
    bool isOpened;
} Inventory;



Inventory* InventoryCreate(int capacity);
void InventoryAddObject(Inventory* inventory, Object* object);
void InventoryRemoveObject(Inventory* inventory, Object object);
void InventoryDestroy(Inventory* inventory);
void InventoryPrint(Inventory* inventory);
