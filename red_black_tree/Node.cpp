#include "Node.hpp"

Node::Node(int key) {
    this->key = key;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = false;
}

Node::Node(int key, Node *left, Node *right, Node *parent, bool color) {
    this->key = key;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->color = color;
}
