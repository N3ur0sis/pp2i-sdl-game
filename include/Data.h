/*
* @file Data.h
* @brief Data header file
* 
* @author VD
*/

#ifndef PP2I_DATA_H
#define PP2I_DATA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Vector.h"
#include "Type.h"

typedef struct _Data Data;
typedef struct _Vector Vector;

/*
* @brief Structure representing a data.
*
* This structure represents a data that can be of type int, float, string or vector.
*/
struct _Data {
    Type type;              /**< Type of the data */
    union {                 
        int i;
        float f;
        char str[20];
        Vector* vector;
    } value;                /**< Value of the data */
};

/*
* @brief Creates a new Data instance of type int.
*
* This function creates a new Data instance of type int.
*
* @param value The value of the data.
* @return Pointer to the created Data instance or NULL on failure.
*/
Data* createIntData(int value);

/*
* @brief Creates a new Data instance of type float.
*
* This function creates a new Data instance of type float.
*
* @param value The value of the data.
* @return Pointer to the created Data instance or NULL on failure.
*/
Data* createFloatData(float value);

/*
* @brief Creates a new Data instance of type string.
*
* This function creates a new Data instance of type string.
*
* @param value The value of the data.
* @return Pointer to the created Data instance or NULL on failure.
*/
Data* createStringData(char* value);

/*
* @brief Creates a new Data instance of type vector.
*
* This function creates a new Data instance of type vector.
*
* @param value The value of the data.
* @return Pointer to the created Data instance or NULL on failure.
*/
Data* createVectorData(Vector* value);

/*
* @brief Verifies if two Data instances are equal.
*
* This function verifies if two Data instances are equal.
*
* @param data1 The first Data instance.
* @param data2 The second Data instance.
* @return true if the Data instances are equal, false otherwise.
*/
bool equalsData(Data* data1, Data* data2);

/*
* @brief Prints the data.
*
* This function prints the data.
*
* @param data The data to print.
*/
void printData(Data* data);

/*
* @brief Gets the value of the data.
*
* This function gets the value of the data.
*
* @param data The data to get the value from.
* @return Pointer to the value of the data.
*/
void* getValue(Data* data);

/*
* @brief Gets the type of the data.
*
* This function gets the type of the data.
*
* @param data The data to get the type from.
* @return The type of the data.
*/
Type type(Data* data);

#endif //PP2I_DATA_H
