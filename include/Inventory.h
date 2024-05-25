#pragma once
#include <Objects.h>
#include <Renderer.h>
// #include <Controls.h>



typedef struct _Inventory {
    Object** objects;
    int size;
    int capacity;
    bool isOpened;
} Inventory;






Inventory* InventoryCreate(int capacity);
void InventoryAddObject(Inventory* inventory, Object* object);
void InventoryRemoveObject(Inventory* inventory, Object object);
void InventoryPrint(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y);
int InventoryPrintTrade(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y, int mouse_x, int mouse_y, bool* hasClicked);
void freeInventory(Inventory* inventory);
bool MouseOnCase(int x_square, int y_square, int mouse_x, int mouse_y);
