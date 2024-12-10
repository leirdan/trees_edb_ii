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

    // Helper function to find the minimum value in a subtree
    AVLnode* minValueNode(AVLnode* node) {
        AVLnode* new_node = node;
        while (new_node->left != nullptr) {
            new_node = new_node->left;
        }
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
    AVLnode* rightRotation(AVLnode* node) {
        AVLnode* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        new_node->height = 1 + std::max(getHeight(new_node->left), getHeight(new_node->right));

        return new_node;
    }

    // Recursive helper function to find a node in the AVL tree
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

    // Iterative helper function to find a node in the AVL tree
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

    // Helper function to insert a new node into the AVL tree
    AVLnode* insertNode(AVLnode* root, int key) {
        if (root == nullptr) {
            AVLnode* new_node = new AVLnode(key);
            new_node->key = key;
            new_node->left = new_node->right = nullptr;
        }

        if (key < root->key) {
            root->left = insertNode(root->left, key);
        } else if (key > root->key) {
            root->right = insertNode(root->right, key);
        } else {
            return root;
        }

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        
        int balance = getBalance(root);

        if (balance > 1 && key < root->left->key) {
            return rightRotation(root);
        } else if (balance > 1 && key > root->left->key) {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        } else if (balance < -1 && key > root->right->key) {
            return leftRotation(root);
        } else if (balance < -1 && key < root->right->key) {
            root->right = rightRotation(root);
            return leftRotation(root);
        }

        return root;
    }

    // Helper function to delete a node from the AVL tree
    AVLnode* deleteNode(AVLnode* root, int key) {
        if (root == nullptr) {
            return root;
        }

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLnode* temp = root->left ? root->left : root->right;

                if (temp = nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AVLnode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }                                                        
        } 

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotation(root);
        } else if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotation(root->left);
            return rightRotation(root);
        } else if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotation(root);
        } else if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotation(root);
            return leftRotation(root);
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

    AVLnode* insertNode(int key) {
        return insertNode(root, key);
    }

    AVLnode* deleteNode(int key) {
        return deleteNode(root, key);
    }

};