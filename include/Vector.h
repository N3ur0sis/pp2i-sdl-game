/**
 * @file Vector.h
 * @brief Header file for the vector.
 * @author VD
*/

#ifndef PP2I_VECTOR_H
#define PP2I_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include "Data.h"
#include "Type.h"

typedef struct _Vector Vector;
typedef struct _Data Data;

/**
 * @brief Struct representing a vector.
*/
struct _Vector {
    Data** data;        /**< Array of pointers to the data. */
    int size;       /**< Number of elements in the vector. */
    int capacity;   /**< Capacity of the vector. */
    Type type;    /**< Type of the vector. */
};

/**
 * @brief Function to create a vector.
 * 
 * This function creates a vector.
 * 
 * @param type Type of the vector.
 * @return Pointer to the vector.
 */
Vector* createVector(Type type);

/**
 * @brief Function to get the size of the vector.
 * 
 * This function gets the size of the vector.
 * 
 * @param vector Pointer to the vector.
 * @return Size of the vector.
 */
int size(Vector* vector);

/**
 * @brief Function to get the capacity of the vector.
 * 
 * This function gets the capacity of the vector.
 * 
 * @param vector Pointer to the vector.
 * @return Capacity of the vector.
 */
int capacity(Vector* vector);

/**
 * @brief Function to resize the vector.
 * 
 * This function resizes the vector.
 * 
 * @param vector Pointer to the vector.
 * @param size New size of the vector.
 * @param data Pointer to the data.
 */
void resize(Vector* vector, int size, Data* data);

/**
 * @brief Function to check if the vector is empty.
 * 
 * This function checks if the vector is empty.
 * 
 * @param vector Pointer to the vector.
 * @return True if the vector is empty, false otherwise.
 */
bool empty(Vector* vector);

/**
 * @brief Function to reserve space in the vector.
 * 
 * This function reserves space in the vector.
 * 
 * @param vector Pointer to the vector.
 * @param capacity Capacity to reserve.
 */
void reserve(Vector* vector, int capacity);

/**
 * @brief Function to shrink the vector to fit the size.
 * 
 * This function shrinks the vector to fit the size.
 * 
 * @param vector Pointer to the vector.
 */
void shrink_to_fit(Vector* vector);

/**
 * @brief Function to get the data at an index.
 * 
 * This function gets the data at an index.
 * 
 * @param vector Pointer to the vector.
 * @param index Index of the data.
 * @return Pointer to the data.
 */
Data* operator_index(Vector* vector, int index);

/**
 * @brief Function to add data to the end of the vector.
 * 
 * This function adds data to the end of the vector.
 * 
 * @param vector Pointer to the vector.
 * @param data Pointer to the data. 
*/
void push_back(Vector* vector, Data* data);

/**
 * @brief Function to remove data from the end of the vector.
 * 
 * This function removes data from the end of the vector.
 * 
 * @param vector Pointer to the vector.
*/
void pop_back(Vector* vector);

/**
 * @brief Function to insert data at an index.
 * 
 * This function inserts data at an index.
 * 
 * @param vector Pointer to the vector.
 * @param index Index to insert the data.
 * @param data Pointer to the data.
*/
void insert(Vector* vector, int index, Data* data);

/**
 * @brief Function to erase data at an index.
 * 
 * This function erases data at an index.
 * 
 * @param vector Pointer to the vector.
 * @param index Index to erase the data.
*/
void erase(Vector* vector, int index);

/**
 * @brief Function to clear the vector.
 * 
 * This function clears the vector.
 * 
 * @param vector Pointer to the vector.
*/
void clear(Vector* vector);

/**
 * @brief Function to check if two vectors are equal.
 * 
 * This function checks if two vectors are equal.
 * 
 * @param vector1 Pointer to the first vector.
 * @param vector2 Pointer to the second vector.
 * @return True if the vectors are equal, false otherwise.
*/
bool equalsVector(Vector* vector1, Vector* vector2);

/**
 * @brief Function to get the number of elements in the vector.
 * 
 * This function gets the number of elements in the vector.
 * 
 * @param vector Pointer to the vector.
 * @return Number of elements in the vector.
*/
int numElements(Vector* vector);

/**
 * @brief Function to convert a vector to vertices.
 * 
 * This function converts a vector to vertices.
 * 
 * @param vector Pointer to the vector.
 * @return Pointer to the vertices.
*/
GLfloat* toVertices(Vector* vector);

/**
 * @brief Function to convert a vector to indices.
 * 
 * This function converts a vector to indices.
 * 
 * @param vector Pointer to the vector.
 * @return Pointer to the indices.
*/
GLuint* toIndices(Vector* vector);

/**
 * @brief Function to print the vector.
 * 
 * This function prints the vector.
 * 
 * @param vector Pointer to the vector.
*/
void printVector(Vector* vector);

/**
 * @brief Function to destroy the vector.
 * 
 * This function destroys the vector.
 * 
 * @param vector Pointer to the vector.
*/
void destroyVector(Vector* vector);

#endif //PP2I_VECTOR_H
