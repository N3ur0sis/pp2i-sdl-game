/**
 * @file Tree.h
 * @brief Header file for the tree structure.
 * @author VD
*/

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

typedef struct Node Node;
typedef struct _Data Data;

/**
 * @brief Struct representing a node in a tree.
*/
struct Node {
    Data* content;      /**< Pointer to the data of the node. */
    Node** children;    /**< Array of pointers to the children of the node. */
    int childCount;     /**< Number of children of the node. */
};

/**
 * @brief Function to create a node.
 * 
 * This function creates a node.
 * 
 * @param data Pointer to the data.
 * @return Pointer to the node.
 */
Node* createNode(Data* data);

/**
 * @brief Function to add a child to a node.
 * 
 * This function adds a child to a node.
 * 
 * @param parent Pointer to the parent node.
 * @param child Pointer to the child node.
 */
void addChild(Node* parent, Node* child);

/**
 * @brief Function to count the number of children of a node.
 * 
 * This function counts the number of children of a node.
 * 
 * @param parent Pointer to the parent node.
 * @return Number of children.
*/
int childCount(Node* parent);

/**
 * @brief Function to get the depth of a node.
 * 
 * This function gets the depth of a node.
 * 
 * @param root Pointer to the root node.
 * @param node Pointer to the node.
 * @return Depth of the node.
 */
int depth(Node* root, Node* node);

/**
 * @brief Function to get the height of a node.
 * 
 * This function gets the height of a node.
 * 
 * @param root Pointer to the root node.
 * @return Height of the node.
 */
int height(Node* root);

/**
 * @brief Function to print the tree.
 * 
 * This function prints the tree.
 * 
 * @param parent Pointer to the root node.
 */
void BFS(Node* parent);

/**
 * @brief Function to search for a node in the tree.
 * 
 * This function searches for a node in the tree.
 * 
 * @param parent Pointer to the root node.
 * @param data Pointer to the data.
 * @return Pointer to the node.
 */
int search(Node* parent, Data* data);

#endif //PP2I_GRAPH_H
