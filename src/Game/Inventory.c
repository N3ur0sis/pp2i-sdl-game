#include "Inventory.h"


Inventory* InventoryCreate(int capacity) {
    Inventory* inventory = (Inventory*)calloc(1, sizeof(Inventory));
    inventory->objects = (Object*)calloc(capacity, sizeof(Object));
    inventory->size = 0;
    inventory->capacity = capacity;
    inventory->isOpened = false;
    return inventory;
}



void InventoryAddObject(Inventory* inventory, Object* object) {
    if (inventory->size < inventory->capacity) {
        inventory->objects[inventory->size] = *object;
        inventory->size++;
    }
}

void InventoryRemoveObject(Inventory* inventory, Object object) {
    for (int i = 0; i < inventory->size; i++) {
        if (inventory->objects[i].id == object.id) {
            for (int j = i; j < inventory->size - 1; j++) {
                inventory->objects[j] = inventory->objects[j + 1];
            }
            inventory->size--;
            break;
        }
    }
}

void InventoryDestroy(Inventory* inventory) {
    free(inventory->objects);
    free(inventory);
}





void InventoryPrint(Inventory* inventory) {
    for (int i = 0; i < 10; i++) {
        int nb_items = 0;
        for (int k = 0; k < inventory->size; k++ ) {
            if ((inventory->objects[k]).id == i) {
                nb_items++;
            }
        }
        printObject(i, nb_items);
    }
}

