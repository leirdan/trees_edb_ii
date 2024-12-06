#include "node.h"
#include <algorithm>

class AVLTree {
private:
    AVLnode* root;

    // Helper function to get the height of a node
    int getHeight(AVLnode* node) {
        if (node == nullptr) 
            return 0;
        return node->height;
    }

    // Helper function to get the balance factor of a node
    int getBalance(AVLnode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Helper function to perform a left rotation on a subtree if not balanced in the right
    AVLnode* leftRotation(AVLnode* node) {
        AVLnode* new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        new_node->height = 1 + std::max(getHeight(new_node->left), getHeight(new_node->right));

        return new_node;
    }

    // Helper function to perform a right rotation on a subtree if not balanced in the left
    AVLnode* leftRotation(AVLnode* node) {
        AVLnode* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        new_node->height = 1 + std::max(getHeight(new_node->left), getHeight(new_node->right));

        return new_node;
    }

    


public:

};