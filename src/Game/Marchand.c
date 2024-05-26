#include <Marchand.h>


int currentIdObject = -1;
bool hasClicked = false;
int origin = -1;
bool clickAction = false;


Entity* createMarchand(Scene* scene, vec3 position, vec3 scale, vec3 rotation) {
    Entity* marchandEntity = createEntity(scene);
    if (marchandEntity != NULL) {
        Model* marchand = (Model*)calloc(1, sizeof(Model));
        ModelCreate(marchand, "assets/models/start/marchang.obj");
        marchand->isRenderable = true;
        addComponent(marchandEntity, COMPONENT_RENDERABLE, marchand);

        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->position[0] = position[0];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->position[1] = position[1];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->position[2] = position[2];

        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->scale[0] = scale[0];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->scale[1] = scale[1];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->scale[2] = scale[2];

        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->rotation[0] = rotation[0];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->rotation[1] = rotation[1];
        ((Model*)getComponent(marchandEntity, COMPONENT_RENDERABLE))->rotation[2] = rotation[2]; 

        Collider* marchandCollision = ColliderCreate("assets/models/start/marchang.obj");
        glm_translate_make(marchandCollision->transformMatrix, position);
        UpdateCollider(marchandCollision);
        addComponent(marchandEntity, COMPONENT_COLLIDER, marchandCollision);
    }
    return marchandEntity;
}


void talkToMarchandStart(float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy) {
    SDL_Color color_black = {0, 0, 0, 0};
    SDL_Color color_white = {255, 255, 255, 0};
    switch (*click_counter) {
    case 0:
        RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
        RenderText("Bien le bonjour, c'est une bonne journée", color_black, window_width / 2, window_height / 15 + 140 , 30, window_width, window_height, shader);
        RenderText("n'est ce pas ?", color_black, window_width / 2, window_height / 15 + 110, 30, window_width, window_height, shader);
        RenderText("               Cliquez pour continuer...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
        RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 1:
        RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
        RenderText("Aurais-tu quelques sous à m'échanger", color_black, window_width / 2, window_height / 15 + 140 , 30, window_width, window_height, shader);
        RenderText("contre des babioles ?", color_black, window_width / 2, window_height / 15 + 110, 30, window_width, window_height, shader);
        RenderText("               Cliquez pour continuer...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
        RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 2:
        RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
        RenderText("Je suis désolé, je n'ai rien à t'offrir", color_black, window_width / 2, window_height / 15 + 140 , 30, window_width, window_height, shader);
        RenderText("pour le moment.", color_black, window_width / 2, window_height / 15 + 110, 30, window_width, window_height, shader);
        RenderText("               Cliquez pour continuer...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
        RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);     
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter) = 0;
            *isBusy = false;
            *is_clicking = true;

        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
    default:
        break;
    }
}


void talkToMarchandMain(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader, int* click_counter, bool* is_clicking, bool* isBusy, int* money) {
    SDL_Color color_black = {0, 0, 0, 0};
    SDL_Color color_white = {255, 255, 255, 0};
    switch (*click_counter) {
    case 0:
        RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
        RenderText("Bien le bonjour, c'est une bonne journée", color_black, window_width / 2, window_height / 15 + 140 , 30, window_width, window_height, shader);
        RenderText("n'est ce pas ?", color_black, window_width / 2, window_height / 15 + 110, 30, window_width, window_height, shader);
        RenderText("               Cliquez pour continuer...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
        RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 1:
        RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
        RenderText("Aurais tu quelques sous à m'échanger", color_black, window_width / 2, window_height / 15 + 140 , 30, window_width, window_height, shader);
        RenderText("contre des babioles ?", color_black, window_width / 2, window_height / 15 + 110, 30, window_width, window_height, shader);
        RenderText("               Cliquez pour continuer...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
        RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);
        if (getMouseButtonState(1) && !*is_clicking) {
            (*click_counter)++;
            *is_clicking = true;
        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
        break;
    case 2:
        tradingWithMarchand(inventory, marchantInventory, window_width, window_height, shader, click_counter, is_clicking, isBusy, money);
        if (getKeyState(SDLK_f) && !*is_clicking) {
            (*click_counter) = 0;
            *isBusy = false;
            *is_clicking = true;

        }
        if (!getMouseButtonState(1)) {
            *is_clicking = false;
        }
    default:
        break;
    }
}



void tradingWithMarchand(Inventory* inventory, Inventory* marchantInventory, float window_width, float window_height, GLuint shader,int* click_counter, bool* is_clicking, bool* isBusy, int* money) {
    SDL_Color color_black = {0, 0, 0, 0};
    SDL_Color color_white = {255, 255, 255, 0};
    SDL_Color color_yellow = {255, 215, 0, 255};
    bool isClickingMarchand = getMouseButtonState(1);
    int pos_x = getMousePosition(0);
    int pos_y = getMousePosition(1);
    int id_joueur = InventoryPrintTrade(inventory, window_width, window_height, shader, -300, 150, pos_x, pos_y, &hasClicked, isClickingMarchand);
    int id_marchand = InventoryPrintTrade(marchantInventory, window_width, window_height, shader, +300, 150, pos_x, pos_y, &hasClicked, isClickingMarchand);
    if (hasClicked) {
        hasClicked = false;
        if (id_joueur != -1) {
            currentIdObject = id_joueur;
            origin = 0;
        } else {
            currentIdObject = id_marchand;
            origin = 1;
        }
    }
    if (currentIdObject != -1) {
        if (origin == 0) {
            if (checkWantToTrade(pos_x, pos_y, window_width, window_height)) {
                RenderText("--> VENDRE <--", color_yellow, window_width / 2, window_height / 3 + 90, 30, window_width, window_height, shader); 
                char prix[12];
                sprintf(prix, "%d Sushis", costFromId(currentIdObject));
                RenderText(prix, color_black, window_width / 2, window_height / 3 + 140, 30, window_width, window_height, shader);
                if (getMouseButtonState(1) && !clickAction) {
                    InventoryRemoveObject(inventory, currentIdObject);
                    *money += costFromId(currentIdObject);
                    clickAction = true;
                } else if (!getMouseButtonState(1)) {
                    clickAction = false;
                }
            } else {
                RenderText("VENDRE", color_black, window_width / 2, window_height / 3 + 90, 30, window_width, window_height, shader);
                char prix[12];
                sprintf(prix, "%d Sushis", costFromId(currentIdObject));
                RenderText(prix, color_black, window_width / 2, window_height / 3 + 140, 30, window_width, window_height, shader);
            }
            char* path = checkIdObject(currentIdObject);
            RenderImage(path, window_width / 2, window_height / 2 + 105 , window_width, window_height, shader);
            free(path);
        } else {
            if (checkWantToTrade(pos_x, pos_y, window_width, window_height)) {
                RenderText("--> ACHETER <--", color_yellow, window_width / 2, window_height / 3 + 90, 30, window_width, window_height, shader); 
                char prix[12];
                sprintf(prix, "%d Sushis", costFromId(currentIdObject));
                RenderText(prix, color_black, window_width / 2, window_height / 3 + 140, 30, window_width, window_height, shader);
                printf("cost : %d\n", costFromId(currentIdObject));
                if (getMouseButtonState(1) && !clickAction) {
                    bool isPResent = InventoryRemoveObject(marchantInventory, currentIdObject);
                    if (isPResent) {
                        InventoryAddObjects(1, inventory, Object_createFromId(currentIdObject));
                        *money -= costFromId(currentIdObject);
                    } 
                    clickAction = true;
                } else if (!getMouseButtonState(1)) {
                    clickAction = false;
                }
            } else {
                RenderText("ACHETER", color_black, window_width / 2, window_height / 3 + 90, 30, window_width, window_height, shader);
                char prix[12];
                sprintf(prix, "%d Sushis", costFromId(currentIdObject));
                RenderText(prix, color_black, window_width / 2, window_height / 3 + 140, 30, window_width, window_height, shader);
            }
            char* path = checkIdObject(currentIdObject);
            RenderImage(path, window_width / 2, window_height / 2 + 105 , window_width, window_height, shader);
            free(path);
        }
    }
    RenderText("Sushis en poche :           ", color_black, window_width / 2 - 100, window_height / 15 + 140, 30, window_width, window_height, shader);
    char money_str[12];
    sprintf(money_str, " %d", *money);
    RenderText(money_str, color_black, window_width / 2, window_height / 15 + 140, 30, window_width, window_height, shader);
    
    RenderText("   Marchand         ", color_white, window_width / 2 - 175, window_height / 15 + 200, 25, window_width, window_height, shader);
    RenderText("Que veux tu échanger ?                ", color_black, window_width / 2, window_height / 15 + 90 , 30, window_width, window_height, shader);
    RenderText("            Appuie sur f pour quitter...", color_black, window_width / 2 + 45, window_height / 15 + 50, 25, window_width, window_height, shader);
    RenderImage("assets/images/dialog-box.png", window_width / 2, window_height / 15, window_width, window_height, shader);
    RenderImage("assets/images/Inventory_Slot_1.png", window_width / 2, window_height / 2 + 85 , window_width, window_height, shader);
}



bool checkWantToTrade(int x, int y, float window_width, float window_height) {
    if (x > window_width / 2 - 80 && x < window_width / 2 + 80 && y < (window_height - (window_height / 3 + 90  - 23)) && y  > (window_height - (window_height / 3 + 90  + 23))) {
        return true;
    }
    return false;
}