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





void InventoryPrint(Inventory* inventory, GameState* gameState, Scene* scene) {
    int nb_items_non_nuls = 0;
    for (int i = 0; i < 10; i++) {
        int nb_items = 0;
        for (int k = 0; k < inventory->size; k++ ) {
            if ((inventory->objects[k]).id == i) {
                nb_items++;
            }
        }
        if (!(nb_items == 0)) {
            int lignes = nb_items_non_nuls / 3;
            int colonnes = nb_items_non_nuls % 3;
            char nb[12];
            sprintf(nb, "%d", nb_items);
            SDL_Color color_red = {255, 0, 0, 0};
            RenderText(nb, color_red, gameState->g_WindowWidth / 2 - 56 + 69 *colonnes , gameState->g_WindowHeight / 3 + 172 - 69 * lignes, 15, gameState->g_WindowWidth,gameState->g_WindowHeight, scene->textShader->m_program);
            if (nb_items_non_nuls % 2 == 1) {
                RenderImage("assets/images/Heart_Orange_1.png", gameState->g_WindowWidth / 2 -70 + 69 * colonnes  , gameState->g_WindowHeight / 3 + 165 - 68 * lignes , gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            } else {
                RenderImage("assets/images/Heart_Blue_1.png", gameState->g_WindowWidth / 2 -70 + 69 * colonnes  , gameState->g_WindowHeight / 3 + 165 - 68 * lignes , gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);
            }
            nb_items_non_nuls++;
        }
        
    }
    RenderImage("assets/images/Inventory_Example_03.png", gameState->g_WindowWidth / 2, gameState->g_WindowHeight / 3, gameState->g_WindowWidth, gameState->g_WindowHeight, scene->textShader->m_program);

}

