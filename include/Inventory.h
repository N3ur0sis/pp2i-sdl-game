/**
 * @file Inventory.h
 * @brief Header file for the inventory component.
*/

#pragma once
#include <Objects.h>
#include <Renderer.h>
// #include <Controls.h>


/**
 * @brief Struct representing an inventory.
 * 
 * This struct represents an inventory.
 * 
 */
typedef struct _Inventory {
    Object** objects;       /**< Array of objects in the inventory. */
    int size;               /**< Number of objects in the inventory. */
    int capacity;           /**< Capacity of the inventory. */
    bool isOpened;          /**< Boolean flag indicating if the inventory is open. */
} Inventory;

/**
 * @brief Function to create an inventory.
 * 
 * This function creates an inventory.
 * 
 * @param capacity Capacity of the inventory.
 * @return Pointer to the inventory.
 */
Inventory* InventoryCreate(int capacity);

/**
 * @brief Function to add an object to the inventory.
 * 
 * This function adds an object to the inventory.
 * 
 * @param inventory Pointer to the inventory.
 * @param object Pointer to the object.
 */
void InventoryAddObjects(int nb, Inventory* inventory, Object* object);

/**
 * @brief Function to remove an object from the inventory.
 * 
 * This function removes an object from the inventory.
 * 
 * @param inventory Pointer to the inventory.
 * @param id ID of the object.
 * @return Boolean value indicating if the object was removed.
 */
bool InventoryRemoveObject(Inventory* inventory, int id);

/**
 * @brief Function to print the inventory.
 * 
 * This function prints the inventory.
 * 
 * @param inventory Pointer to the inventory.
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @param shader Shader program.
 * @param offset_x X offset.
 * @param offset_y Y offset.
 */
void InventoryPrint(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y);

/**
 * @brief Function to print the inventory of the trade.
 * 
 * This function prints the inventory of the trade.
 * 
 * @param inventory Pointer to the inventory.
 * @param window_width Width of the window.
 * @param window_height Height of the window.
 * @param shader Shader program.
 * @param offset_x X offset.
 * @param offset_y Y offset.
 * @param mouse_x X position of the mouse.
 * @param mouse_y Y position of the mouse.
 * @param hasClicked Pointer to the boolean flag indicating if the inventory has been clicked.
 * @param isClickingMarchand Boolean flag indicating if the inventory is being clicked.
 * @return Boolean value indicating if the inventory is being clicked.
 */
int InventoryPrintTrade(Inventory* inventory, float window_width, float window_height, GLuint shader, float offset_x, float offset_y, int mouse_x, int mouse_y, bool* hasClicked, bool isClickingMarchand);

/**
 * @brief Function to free the inventory.
 * 
 * This function frees the inventory.
 * 
 * @param inventory Pointer to the inventory.
 */
void freeInventory(Inventory* inventory);

/**
 * @brief Function to check if the mouse is on a case.
 * 
 * This function checks if the mouse is on a case.
 * 
 * @param x_square X position of the square.
 * @param y_square Y position of the square.
 * @param mouse_x X position
 * @param mouse_y Y position
 * @return Boolean value indicating if the mouse is on the case.
 */
bool MouseOnCase(int x_square, int y_square, int mouse_x, int mouse_y);

/**
 * @brief Function to print the inventory.
 * 
 * This function prints the inventory.
 * 
 * @param inventory Pointer to the inventory.
 */
void printInventorySimple(Inventory* inventory);