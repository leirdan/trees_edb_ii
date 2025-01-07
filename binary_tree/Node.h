#ifndef NODE_H
#define NODE_H

/// @brief Nó da Árvore Binária.
/// @details Este nó é utilizado para construir a árvore binária, onde cada nó 
/// contém um valor inteiro e referências para seus filhos esquerdo e direito.
struct Node {
    int key;/// @brief Nó da Árvore Binária.
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

#endif