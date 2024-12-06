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

    // Recursive helper function to find the key in a node 
    AVLnode* searchRecursive(AVLnode* root, int key) {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return searchRecursive(root->left, key);
        }
        if (key > root->key) {
            return searchRecursive(root->right, key);
        }
    }

    // Iterative helper function to find the key in a root
    AVLnode* searchIterative(AVLnode* root, int key) {
        while (root != nullptr && root->key != key) {
            if (key < root->key) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return root;
    }


public:

    AVLTree() : root(nullptr) {}

    AVLnode* searchRecursive(int key) {
        return searchRecursive(root, key);
    }

    AVLnode* searchIterative(int key) {
        return searchIterative(root, key);
    }

};