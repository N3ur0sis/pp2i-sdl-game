#pragma once
#include <Objects.h>
#include <Renderer.h>
#include <stdlib.h>


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
void InventoryPrint(Inventory* inventory, float window_width, float window_height, GLuint shader);