#include "BinaryTree.h"
#include <iostream>
#include <queue>
using namespace std;

BinaryTree::BinaryTree() : root(nullptr) {}

Node* BinaryTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    return node;
}

Node* BinaryTree::search(Node* node, int value) {
    if (node == nullptr || node->data == value) {
        return node;
    }
    if (value < node->data) {
        return search(node->left, value);
    }
    return search(node->right, value);
}

Node* BinaryTree::findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* BinaryTree::remove(Node* node, int value) {
    if (node == nullptr) {
        return node;
    }
    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }
    return node;
}

void BinaryTree::preOrderTraversal(Node* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void BinaryTree::inOrderTraversal(Node* node) {
    if (node == nullptr) return;
    inOrderTraversal(node->left);
    cout << node->data << " ";
    inOrderTraversal(node->right);
}

void BinaryTree::postOrderTraversal(Node* node) {
    if (node == nullptr) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->data << " ";
}

void BinaryTree::levelOrderTraversal(Node* node) {
    if (node == nullptr) return;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

void BinaryTree::insert(int value) {
    root = insert(root, value);
}

bool BinaryTree::search(int value) {
    return search(root, value) != nullptr;
}

void BinaryTree::remove(int value) {
    root = remove(root, value);
}

void BinaryTree::displayPreOrder() {
    preOrderTraversal(root);
    cout << endl;
}

void BinaryTree::displayInOrder() {
    inOrderTraversal(root);
    cout << endl;
}

void BinaryTree::displayPostOrder() {
    postOrderTraversal(root);
    cout << endl;
}

void BinaryTree::displayLevelOrder() {
    levelOrderTraversal(root);
    cout << endl;
}
