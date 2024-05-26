/**
 * @file List.h
 * @brief Header file for the list component.
*/

#pragma once

#include <stdlib.h>
#include "stdio.h"

/**
 * @brief Struct representing a list.
 * 
 * This struct represents a list.
*/
typedef struct _List{
    int val;                /**< Value of the list. */
    struct _List *next;     /**< Pointer to the next element of the list. */
} List;

/**
 * @brief Function to create a list.
 * 
 * This function creates a list.
 * 
 * @param val Value of the list.
 * @param next Pointer to the next element of the list.
 * @return Pointer to the list.
 */
List *create_list(int val, List *next);

/**
 * @brief Function to free a list.
 * 
 * This function frees a list.
 * 
 * @param Liste Pointer to the list.
 */
void free_list(List *Liste);

/**
 * @brief Function to print a list.
 * 
 * This function prints a list.
 * 
 * @param L Pointer to the list.
 */
void printL(List *L);

/**
 * @brief Function to get the length of a list.
 * 
 * This function gets the length of a list.
 * 
 * @param L Pointer to the list.
 * @return Length of the list.
 */
int len(List*L);

/**
 * @brief Function to append a value to a list.
 * 
 * This function appends a value to a list.
 * 
 * @param head Pointer to the head of the list.
 * @param value Value to append.
 */
void append(List **head, int value);

/**
 * @brief Function to remove the last element of a list.
 * 
 * This function removes the last element of a list.
 * 
 * @param head Pointer to the head of the list.
 */
void removeLast(List **head);