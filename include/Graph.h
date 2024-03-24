//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "Vector.h"

typedef struct _Graph Graph;
typedef struct _Data Data;

struct _Graph {
    Vector** adjacencyList;
    int size;
    Type type;
    Vector* data;
};


Graph* createGraph(Type type);

int sizeGraph(Graph* graph);

void addVertex(Graph* graph, Data* data);

void addEdge(Graph* graph, int vertex1, int vertex2);

bool emptyGraph(Graph* graph);

void destroyGraph(Graph* graph);

#endif //PP2I_GRAPH_H
