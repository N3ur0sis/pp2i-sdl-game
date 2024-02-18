//
// Created by Victor Davillé on 17/02/2024.
//

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdlib.h>
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

void printData(union Data data);

typedef struct Node Node;

struct Node {
    union Data content;
    Node** children;
    int childCount;
};

Node* createNode(int i);

void addChild(Node* parent, Node* child);

int childCount(Node* parent);

int depth(Node* root, Node* node);

int height(Node* root);

void BFS(Node* parent);

#endif //PP2I_GRAPH_H
