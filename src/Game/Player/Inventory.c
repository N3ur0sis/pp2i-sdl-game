#include "Inventory.h"



Inventory* InventoryCreate(int capacity) {
    Inventory* inventory = (Inventory*)calloc(1, sizeof(Inventory));
    inventory->objects = (Object**)calloc(capacity, sizeof(Object));
    inventory->size = 0;
    inventory->capacity = capacity;
    inventory->isOpened = false;
    return inventory;
}



void InventoryAddObjects(int nb, Inventory* inventory, Object* object) {
    for (int i = 0; i < nb; i++) {
        if (inventory->size < inventory->capacity) {
            inventory->objects[inventory->size] = object;
            inventory->size++;
        }
    }
}



bool InventoryRemoveObject(Inventory* inventory, int id) {
    //Premier parcours pour vérifier si un objet de est bien présent dans l'inventaire
    bool isPresent = false;
    for (int i = 0; i < inventory->size; i++) {
        if (inventory->objects[i]->id == id) {
            isPresent = true;
            break;
        }
    }
    //Si l'objet est présent, on crée un nouvel inventaire, on copie l'ancien sans l'objet en question et on remplace l'ancien par le nouveau
    if (isPresent) {
        bool found = false;
        Inventory* newInventory = InventoryCreate(inventory->capacity);
        for (int i = 0; i < inventory->size; i++) {
            if (inventory->objects[i]->id != id || found) {
                InventoryAddObjects(1, newInventory, inventory->objects[i]);
            } else {
                found = true;
            }
        }
        // Inventory* tmp = inventory;
        *inventory = *newInventory;
        // freeInventory(tmp);
    }
    return isPresent;
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
    if (inventory->size == 0) {
        RenderImage("assets/images/Inventory_Example_03.png", offset_x + window_width / 2, offset_y + window_height / 3, window_width, window_height, shader);
        return;
    }
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


int InventoryPrintTrade(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y, int mouse_x, int mouse_y, bool* hasClicked, bool isClickingMarchand) {
    if (inventory->size == 0) {
        RenderImage("assets/images/Inventory_Example_03.png", offset_x + window_width / 2, offset_y + window_height / 3, window_width, window_height, shader);
        return -1;
    }
    int renduId = -1;
    int nb_items_non_nuls = 0;
    for (int i = 0; i < 10; i++) {
        int nb_items = 0;
        for (int k = 0; k < inventory->size; k++ ) {
            printf("k : %d\n", k);
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
            RenderImage(path, offset_x + window_width / 2 -70 + 69 * colonnes  , offset_y + window_height / 3 + 165 - 69 * lignes , window_width, window_height, shader);
            free(path);
            if (MouseOnCase(offset_x + window_width / 2 -70 + 69 * colonnes, window_height - (offset_y + window_height / 3 + 165 - 69 * lignes), mouse_x, mouse_y)) {
                RenderImage("assets/images/pixil-frame-0.png", offset_x + window_width / 2 - 69 + 69 * colonnes, offset_y + window_height / 3 + 159 - 69 * lignes , window_width, window_height, shader);
                if (isClickingMarchand && !*hasClicked) {
                    *hasClicked = true;
                    renduId = i;
                }
                if (!isClickingMarchand) {
                    *hasClicked = false;
                }
            }
            nb_items_non_nuls++;
        }
        
    }
    RenderImage("assets/images/Inventory_Example_03.png", offset_x + window_width / 2, offset_y + window_height / 3, window_width, window_height, shader);
    return renduId;
}


bool MouseOnCase(int x_square, int y_square, int mouse_x, int mouse) {
    if ((mouse_x > x_square - 25) && (mouse_x < x_square + 28) && (mouse > y_square - 47) && (mouse < y_square + 3)) {
        return true;
    }
    return false;
}



void printInventorySimple(Inventory* inventory) {
    for (int i = 0; i < inventory->size; i++) {
        printf("Object %d : %s\n", i, inventory->objects[i]->name);
    }
    printf("\n");
}