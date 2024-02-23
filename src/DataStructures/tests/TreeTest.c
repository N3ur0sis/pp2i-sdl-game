//
// Created by Victor Davillé on 17/02/2024.
//

#include "../Tree.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    Node* root = createNode(createIntData(10));
    Node* child1 = createNode(createIntData(1));
    Node* child2 = createNode(createIntData(12));
    addChild(root, child1);
    addChild(root, child2);
    Node* child3 = createNode(createIntData(2));
    addChild(child1, child3);
    Node* child4 = createNode(createIntData(3));
    addChild(child1, child4);
    Node* child5 = createNode(createIntData(4));
    addChild(child2, child5);
    Node* child6 = createNode(createIntData(5));
    addChild(child2, child6);
    Node* child7 = createNode(createIntData(6));
    addChild(child3, child7);
    Node* child8 = createNode(createIntData(7));
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
    assert(depth(root, root) == 0);
    assert(depth(root, child1) == 1);
    assert(depth(root, child2) == 1);
    assert(depth(root, child3) == 2);
    assert(depth(root, child4) == 2);
    assert(depth(root, child5) == 2);
    assert(depth(root, child6) == 2);
    assert(depth(root, child7) == 3);
    assert(depth(root, child8) == 3);
    assert(height(root) == 3);
    assert(height(child1) == 2);
    assert(height(child2) == 1);
    assert(height(child3) == 1);
    assert(height(child4) == 0);
    assert(height(child5) == 0);
    assert(height(child6) == 0);
    assert(height(child7) == 0);
    assert(height(child8) == 0);
    assert(search(root, createIntData(1)));
    assert(search(root, createIntData(12)));
    assert(search(root, createIntData(2)));

    return 0;
}
