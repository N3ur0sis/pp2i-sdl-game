/**
 * @file Graph.h
 * @brief Header file for the graph component.
 * @author VD
*/

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "Vector.h"

typedef struct _Graph Graph;
typedef struct _Data Data;

/**
 * @brief Struct representing a graph.
 * 
 * This struct represents a graph.
*/
struct _Graph {
    Vector** adjacencyList; /**< Adjacency list of the graph. */
    int size;               /**< Size of the graph. */
    Type type;              /**< Type of the graph. */
    Vector* data;           /**< Vector of data. */
};


/**
 * @brief Function to create a graph.
 * 
 * This function creates a graph.
 * 
 * @param type Type of the graph.
 * @return Pointer to the graph.
 */
Graph* createGraph(Type type);

/**
 * @brief Function to get the size of the graph.
 * 
 * This function gets the size of the graph.
 * 
 * @param graph Pointer to the graph.
 * @return Size of the graph.
 */
int sizeGraph(Graph* graph);

/**
 * @brief Function to add a vertex to the graph.
 * 
 * This function adds a vertex to the graph.
 * 
 * @param graph Pointer to the graph.
 * @param data Pointer to the data.
 */
void addVertex(Graph* graph, Data* data);

/**
 * @brief Function to add an edge to the graph.
 * 
 * This function adds an edge to the graph.
 * 
 * @param graph Pointer to the graph.
 * @param vertex1 Index of the first vertex.
 * @param vertex2 Index of the second vertex.
 */
void addEdge(Graph* graph, int vertex1, int vertex2);

/**
 * @brief Function to empty the graph.
 * 
 * This function empties the graph.
 * 
 * @param graph Pointer to the graph.
 * @return Boolean value indicating if the graph is empty.
 */
bool emptyGraph(Graph* graph);

/**
 * @brief Function to destroy the graph.
 * 
 * This function destroys the graph.
 * 
 * @param graph Pointer to the graph.
 */
void destroyGraph(Graph* graph);

#endif //PP2I_GRAPH_H
