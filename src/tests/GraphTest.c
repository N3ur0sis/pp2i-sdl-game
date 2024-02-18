//
// Created by Victor Davillé on 17/02/2024.
//

#include "../Graph.h"
#include <assert.h>

int main(void) {
    Node* root = createNode(0);
    Node* child1 = createNode(1);
    Node* child2 = createNode(2);
    addChild(root, child1);
    addChild(root, child2);
    Node* child3 = createNode(3);
    addChild(child1, child3);
    Node* child4 = createNode(4);
    addChild(child1, child4);
    Node* child5 = createNode(5);
    addChild(child2, child5);
    Node* child6 = createNode(6);
    addChild(child2, child6);
    Node* child7 = createNode(7);
    addChild(child3, child7);
    Node* child8 = createNode(8);
    addChild(child3, child8);
    assert(childCount(root) == 2);
    assert(childCount(child1) == 2);
    assert(childCount(child2) == 2);
    assert(childCount(child3) == 2);
    assert(childCount(child4) == 0);
    assert(childCount(child5) == 0);
    assert(childCount(child6) == 0);
    assert(childCount(child7) == 0);
    assert(childCount(child8) == 0);
    printf("Depth of root: %d\n", depth(root, root));
    printf("Height of root: %d\n", height(root));
    BFS(root);
    return 0;
}
