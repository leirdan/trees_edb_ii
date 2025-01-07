#include "BinaryTree.h"
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/// @brief Construtor da classe BinaryTree
BinaryTree::BinaryTree() : root(nullptr) {}

/// @brief Constrói uma árvore binária balanceada a partir de uma lista
Node* BinaryTree::buildBalancedTree(vector<int>& key, int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    // Criar um nó com o valor do ponto médio
    Node* node = new Node(key[mid]);
    // Recursão para o lado esquerdo e direito
    node->left = buildBalancedTree(key, start, mid - 1);  
    node->right = buildBalancedTree(key, mid + 1, end);
    return node;
}

/// @brief Insere um elemento na árvore
Node* BinaryTree::insert(Node* node, int value) {
     // Se o nó é vazio, cria um novo nó
    if (node == nullptr) return new Node(value);
     // Insere à esquerda se o valor for menor e à direita se o valor for maior
    if (value < node->key) node->left = insert(node->left, value);
    else if (value > node->key) node->right = insert(node->right, value);
    return node;
}

/// @brief Busca um elemento na árvore
Node* BinaryTree::search(Node* node, int value) {
     // Encontra o nó ou retorna nullptr
    if (node == nullptr || node->key == value) return node;
    // Pesquisa à esquerda e à direita
    if (value < node->key) return search(node->left, value);
    return search(node->right, value);
}

/// @brief Encontra o menor nó na subárvore
Node* BinaryTree::findMin(Node* node) {
    while (node && node->left != nullptr) node = node->left;
    return node;
}

/// @brief Remove um nó da árvore
Node* BinaryTree::remove(Node* node, int value) {
    if (node == nullptr) return node;
    if (value < node->key) node->left = remove(node->left, value);
    else if (value > node->key) node->right = remove(node->right, value);
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
         // Encontra o sucessor, substituilo  e remover o suvessor da direita 
        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }
    return node;
}

/// @brief Percurso pré-ordem (raiz, esquerda, direita)
void BinaryTree::preOrderTraversal(Node* node) {
    if (node == nullptr) return;
    cout << node->key << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

/// @brief Percurso em ordem simétrica (esquerda, raiz, direita)
void BinaryTree::inOrderTraversal(Node* node) {
    if (node == nullptr) return;
    inOrderTraversal(node->left);
    cout << node->key << " ";
    inOrderTraversal(node->right);
}

/// @brief Percurso pós-ordem (esquerda, direita, raiz)
void BinaryTree::postOrderTraversal(Node* node) {
    if (node == nullptr) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    cout << node->key << " ";
}

/// @brief Percurso em nível (nível por nível)
void BinaryTree::levelOrderTraversal(Node* node) {
    if (node == nullptr) return;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->key << " ";
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

void BinaryTree::buildTree(vector<int>& key) {
    sort(key.begin(), key.end());
    root = buildBalancedTree(key, 0, key.size() - 1);
}

/// @brief Insere um valor na árvore
void BinaryTree::insert(int value) {
    root = insert(root, value);
}

/// @brief Verifica se um valor existe na árvore
bool BinaryTree::search(int value) {
    return search(root, value) != nullptr;
}

/// @brief Remove um valor da árvore
void BinaryTree::remove(int value) {
    root = remove(root, value);
}

/// @brief Exibe a árvore em pré-ordem
void BinaryTree::displayPreOrder() {
    preOrderTraversal(root);
    cout << endl;
}

/// @brief Exibe a árvore em ordem
void BinaryTree::displayInOrder() {
    inOrderTraversal(root);
    cout << endl;
}

/// @brief Exibe a árvore em pós-ordem
void BinaryTree::displayPostOrder() {
    postOrderTraversal(root);
    cout << endl;
}

/// @brief Exibe a árvore em nível
void BinaryTree::displayLevelOrder() {
    levelOrderTraversal(root);
    cout << endl;
}
