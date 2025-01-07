#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"
#include <vector>

class BinaryTree {
private:
    Node* root;

    Node* buildBalancedTree(std::vector<int>& data, int start, int end);
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
    void buildTree(std::vector<int>& data);
    void insert(int value);
    bool search(int value);
    void remove(int value);

    void displayPreOrder();
    void displayInOrder();
    void displayPostOrder();
    void displayLevelOrder();
    void printTreeDiagram();
};

#endif