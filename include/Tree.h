//
// Created by Victor Davillé on 17/02/2024.
//

#ifndef PP2I_GRAPH_H
#define PP2I_GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"

typedef struct Node Node;
typedef struct _Data Data;

struct Node {
    Data* content;
    Node** children;
    int childCount;
};

Node* createNode(Data* data);

void addChild(Node* parent, Node* child);

int childCount(Node* parent);

int depth(Node* root, Node* node);

int height(Node* root);

void BFS(Node* parent);

int search(Node* parent, Data* data);

#endif //PP2I_GRAPH_H
