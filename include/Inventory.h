#include <Objects.h>
#include <Renderer.h>
#include <SceneManager.h>
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
void InventoryPrint(Inventory* inventory, GameState* gameState, Scene* scene);