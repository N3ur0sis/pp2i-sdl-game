//
// Created by Victor Davillé on 19/02/2024.
//

#include <Graph.h>

Graph* create_graph(int V) {
    Graph* G = (Graph*)malloc(sizeof(Graph));
    G->V = V;
    G->E = 0;
    G->adj = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        G->adj[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            G->adj[i][j] = 0;
        }
    }
    return G;
}

void add_edge(Graph* G, int u, int v) {
    G->adj[u][v] = 1;
    G->adj[v][u] = 1;
    G->E++;
}

void remove_edge(Graph* G, int u, int v) {
    G->adj[u][v] = 0;
    G->adj[v][u] = 0;
    G->E--;
}

void destroy_graph(Graph* G) {
    for (int i = 0; i < G->V; i++) {
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);
}
