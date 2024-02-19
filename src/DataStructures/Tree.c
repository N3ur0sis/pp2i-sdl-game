//
// Created by Victor Davillé on 17/02/2024.
//

#include "Tree.h"

Node* createNode(int i) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->content.i = i;
    newNode->children = NULL;
    newNode->childCount = 0;
    return newNode;
}

void addChild(Node* parent, Node* child) {
    parent->children = (Node **) realloc(parent->children, (parent->childCount + 1) * sizeof(Node*));
    parent->children[parent->childCount] = child;
    parent->childCount++;
}

int childCount(Node* parent) {
    return parent->childCount;
}

int depth(Node* root, Node* node) {
    if (root == node) {
        return 0;
    }
    for (int i = 0; i < root->childCount; i++) {
        int childDepth = depth(root->children[i], node);
        if (childDepth != -1) {
            return childDepth + 1;
        }
    }
    return -1;
}

int height(Node* root) {
    if (root->childCount == 0) {
        return 0;
    }
    int maxHeight = 0;
    for (int i = 0; i < root->childCount; i++) {
        int childHeight = height(root->children[i]);
        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
    }
    return maxHeight + 1;
}

void BFS(Node* parent) {
    Node** queue = malloc(sizeof(Node*));
    int queueSize = 1;
    queue[0] = parent;
    int queueIndex = 0;
    while (queueIndex < queueSize) {
        Node* currentNode = queue[queueIndex];
        printData(currentNode->content);
        for (int i = 0; i < currentNode->childCount; i++) {
            queue = (Node **) realloc(queue, (queueSize + 1) * sizeof(Node*));
            queue[queueSize] = currentNode->children[i];
            queueSize++;
        }
        queueIndex++;
    }
    free(queue);
}

int search(Node* parent, int i) {
    if (parent->content.i == i) {
        return 1;
    }
    for (int j = 0; j < parent->childCount; j++) {
        if (search(parent->children[j], i)) {
            return 1;
        }
    }
    return 0;
}
