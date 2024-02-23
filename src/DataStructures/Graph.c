//
// Created by Victor Davillé on 19/02/2024.
//

#include "Graph.h"

Graph* createGraph(Type type) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    graph->adjacencyList = (Vector**) malloc(10 * sizeof(Vector*));
    if (graph->adjacencyList == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    graph->size = 0;
    graph->type = type;
    graph->data = createVector(type);
    return graph;
}

int sizeGraph(Graph* graph) {
    return graph->size;
}

void addVertex(Graph* graph, Data* data) {
    if (graph->size == graph->data->capacity) {
        reserve(graph->data, graph->size * 2);
    }
    push_back(graph->data, data);
    graph->adjacencyList[graph->size] = createVector(INT);
    graph->size++;
}

void addEdge(Graph* graph, int vertex1, int vertex2) {
    if (vertex1 < 0 || vertex1 >= graph->size || vertex2 < 0 || vertex2 >= graph->size) {
        printf("Invalid vertex\n");
        return;
    }
    push_back(graph->adjacencyList[vertex1], createIntData(vertex2));
    push_back(graph->adjacencyList[vertex2], createIntData(vertex1));
}

bool emptyGraph(Graph* graph) {
    if (graph == NULL) {
        return true;
    }
    return graph->size == 0;
}

void destroyGraph(Graph* graph) {
    for (int i = 0; i < graph->size; i++) {
        destroyVector(graph->adjacencyList[i]);
    }
    free(graph->adjacencyList);
    free(graph);
}
