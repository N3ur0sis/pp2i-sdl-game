#include "Inventory.h"



Inventory* InventoryCreate(int capacity) {
    Inventory* inventory = (Inventory*)calloc(1, sizeof(Inventory));
    inventory->objects = (Object**)calloc(capacity, sizeof(Object));
    inventory->size = 0;
    inventory->capacity = capacity;
    inventory->isOpened = false;
    return inventory;
}



void InventoryAddObject(Inventory* inventory, Object* object) {
    if (inventory->size < inventory->capacity) {
        inventory->objects[inventory->size] = object;
        inventory->size++;
    }
}

void InventoryRemoveObject(Inventory* inventory, Object object) {
    for (int i = 0; i < inventory->size; i++) {
        if (inventory->objects[i]->id == object.id) {
            for (int j = i; j < inventory->size - 1; j++) {
                inventory->objects[j] = inventory->objects[j + 1];
            }
            inventory->size--;
            break;
        }
    }
}

void freeInventory(Inventory* inventory) {
    if (inventory != NULL) {
        // Free the array of objects
        for (int i = 0; i < inventory->size; i++) {
            free(inventory->objects[i]);
        }
        free(inventory->objects);
        // Free the inventory itself
        free(inventory);
    }
}


void InventoryPrint(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y) {
    int nb_items_non_nuls = 0;
    for (int i = 0; i < 10; i++) {
        int nb_items = 0;
        for (int k = 0; k < inventory->size; k++ ) {
            if ((inventory->objects[k])->id == i) {
                nb_items++;
            }
        }
        if (!(nb_items == 0)) {
            int lignes = nb_items_non_nuls / 3;
            int colonnes = nb_items_non_nuls % 3;
            char nb[12];
            sprintf(nb, "%d", nb_items);
            SDL_Color color_red = {255, 0, 0, 0};
            RenderText(nb, color_red, offset_x + window_width / 2 - 56 + 69 *colonnes , offset_y + window_height / 3 + 172 - 69 * lignes, 15, window_width,window_height, shader);
            char* path = checkIdObject(i);
            RenderImage(path, offset_x + window_width / 2 -70 + 69 * colonnes  , offset_y + window_height / 3 + 165 - 68 * lignes , window_width, window_height, shader);
            free(path);
            nb_items_non_nuls++;
        }
    }
    RenderImage("assets/images/Inventory_Example_03.png", offset_x + window_width / 2, offset_y + window_height / 3, window_width, window_height, shader);
}


int InventoryPrintTrade(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y, int mouse_x, int mouse_y) {
    int renduId = -1;
    int nb_items_non_nuls = 0;
    for (int i = 0; i < 10; i++) {
        int nb_items = 0;
        for (int k = 0; k < inventory->size; k++ ) {
            if ((inventory->objects[k])->id == i) {
                nb_items++;
            }
        }
        if (!(nb_items == 0)) {
            int lignes = nb_items_non_nuls / 3;
            int colonnes = nb_items_non_nuls % 3;
            char nb[12];
            sprintf(nb, "%d", nb_items);
            SDL_Color color_red = {255, 0, 0, 0};
            RenderText(nb, color_red, offset_x + window_width / 2 - 56 + 69 *colonnes , offset_y + window_height / 3 + 172 - 69 * lignes, 15, window_width,window_height, shader);
            char* path = checkIdObject(i);
            RenderImage(path, offset_x + window_width / 2 -70 + 69 * colonnes  , offset_y + window_height / 3 + 165 - 68 * lignes , window_width, window_height, shader);
            free(path);
            if (MouseOnCase(offset_x + window_width / 2 - 56 + 69 *colonnes, offset_y + window_height / 3 + 172 - 69 * lignes, mouse_x, mouse_y) && i == 1 ) {
                renduId = i;
            }
            // printf("%d\n", renduId);
            nb_items_non_nuls++;
        }
        
    }
    RenderImage("assets/images/Inventory_Example_03.png", offset_x + window_width / 2, offset_y + window_height / 3, window_width, window_height, shader);

}


bool MouseOnCase(int x_square, int y_square, int mouse_x, int mouse) {
    // if (mouse_x > x_square && mouse_x < x_square + 20 && mouse > y_square && mouse < y_square + 64) {
    //     return true;
    // }
    // return false;
    printf("%d %d %d %d %d %d\n", x_square,x_square+60, y_square, y_square - 60, mouse_x, mouse);
    return false;
}