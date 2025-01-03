#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"

class BinaryTree {
private:
    Node* root;

    Node* insert(Node* node, int value);
    Node* search(Node* node, int value);
    Node* findMin(Node* node);
    Node* remove(Node* node, int value);
    void preOrderTraversal(Node* node);
    void inOrderTraversal(Node* node);
    void postOrderTraversal(Node* node);
    void levelOrderTraversal(Node* node);

public:
    BinaryTree();
    void insert(int value);
    bool search(int value);
    void remove(int value);
    void displayPreOrder();
    void displayInOrder();
    void displayPostOrder();
    void displayLevelOrder();
};

#endif
