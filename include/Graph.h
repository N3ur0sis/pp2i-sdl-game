//
// Created by Victor Davillé on 19/02/2024.
//

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Graph {
    int V;
    int E;
    int **adj;
} Graph;

Graph* create_graph(int V);

void add_edge(Graph* G, int u, int v);

void remove_edge(Graph* G, int u, int v);

void destroy_graph(Graph* G);

#endif //PP2I_GRAPH_H
