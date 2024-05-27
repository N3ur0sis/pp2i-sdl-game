/**
 * @file Objects.h
 * @brief Header file for the objects component.
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * @brief Struct representing an object.
*/
typedef struct _Object {
    char* name;         /**< Name of the object. */
    char* description;  /**< Description of the object. */
    int id;             /**< ID of the object. */
} Object;

/**
 * @brief Function to create an object.
 * 
 * This function creates an object.
 * 
 * @param name Name of the object.
 * @param description Description of the object.
 * @param id ID of the object.
 * @return Pointer to the object.
 */
Object* Object_create(char* name, char* description, int id);

/**
 * @brief Function to create an object from an ID.
 * 
 * This function creates an object from an ID.
 * 
 * @param id ID of the object.
 * @return Pointer to the object.
 */
Object* Object_createFromId(int id);

/**
 * @brief Function to print an object.
 * 
 * This function prints an object.
 * 
 * @param object Pointer to the object.
 */
void printObject(int id, int nb);

/**
 * @brief Function to get the path of an object based on its ID.
 * 
 * This function gets the path of an object based on its ID.
 * 
 * @param id ID of the object.
 * @return Path of the object.
*/
char* checkIdObject(int id);

/**
 * @brief Function to get the name of an object based on its ID.
 * 
 * This function gets the name of an object based on its ID.
 * 
 * @param id ID of the object.
 * @return Name of the object.
*/
char* nameFromId(int id);

/**
 * @brief Function to get the description of an object based on its ID.
 * 
 * This function gets the description of an object based on its ID.
 * 
 * @param id ID of the object.
 * @return Description of the object.
*/
char* descriptionFromId(int id);

/**
 * @brief Function to get the cost of an object based on its ID.
 * 
 * This function gets the cost of an object based on its ID.
 * 
 * @param id ID of the object.
 * @return Cost of the object.
*/
int costFromId(int id);



char* pathToolBar(int id, bool bool1, bool bool2);