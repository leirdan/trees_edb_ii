#include "node.h"
#include <algorithm>
#include <iostream>
#include <queue>

/**
 * @brief Classe que implementa uma Árvore AVL (Adelson-Velsky e Landis).
 * 
 * Estrutura de dados balanceada que garante complexidade O(log n) para
 * as operações de inserção, busca e remoção.
 */
class AVLTree {
private:
    AVLnode* root; ///< Ponteiro para a raiz da árvore.

    /**
     * @brief Obtém a altura de um nó.
     * @param node Ponteiro para o nó cuja altura será calculada.
     * @return A altura do nó. Retorna 0 se o nó for nulo.
     */
    int getHeight(AVLnode* node) {
        if (node == nullptr) 
            return 0;
        return node->height;
    }

    /**
     * @brief Calcula o fator de balanceamento de um nó.
     * @param node Ponteiro para o nó cuja diferença entre as alturas será calculada.
     * @return Fator de balanceamento (altura da subárvore esquerda - altura da subárvore direita).
     */
    int getBalance(AVLnode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    /**
     * @brief Encontra o nó com o menor valor em uma subárvore.
     * @param node Ponteiro para o nó raiz da subárvore.
     * @return Ponteiro para o nó com o menor valor.
     */
    AVLnode* minValueNode(AVLnode* node) {
        AVLnode* new_node = node;
        while (new_node->left != nullptr) {
            new_node = new_node->left;
        }
        return new_node;
    }

    /**
     * @brief Realiza uma rotação à esquerda para balancear a árvore.
     * @param node Ponteiro para o nó que será rotacionado.
     * @return Ponteiro para o novo nó raiz após a rotação.
     */
    AVLnode* leftRotation(AVLnode* node) {
        AVLnode* new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        new_node->height = 1 + std::max(getHeight(new_node->left), getHeight(new_node->right));

        return new_node;
    }

    /**
     * @brief Realiza uma rotação à direita para balancear a árvore.
     * @param node Ponteiro para o nó que será rotacionado.
     * @return Ponteiro para o novo nó raiz após a rotação.
     */
    AVLnode* rightRotation(AVLnode* node) {
        AVLnode* new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        new_node->height = 1 + std::max(getHeight(new_node->left), getHeight(new_node->right));

        return new_node;
    }

    /**
     * @brief Busca recursiva por um nó com a chave especificada.
     * @param root Ponteiro para o nó raiz da subárvore onde a busca será realizada.
     * @param key Valor da chave a ser buscada.
     * @return Ponteiro para o nó encontrado ou nullptr se a chave não existir.
     */
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

    /**
     * @brief Busca iterativa por um nó com a chave especificada.
     * @param root Ponteiro para o nó raiz da subárvore onde a busca será realizada.
     * @param key Valor da chave a ser buscada.
     * @return Ponteiro para o nó encontrado ou nullptr se a chave não existir.
     */
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

    /**
     * @brief Insere um novo nó com a chave especificada na árvore.
     * @param root Ponteiro para o nó raiz da subárvore onde a chave será inserida.
     * @param key Valor da chave a ser inserida.
     * @return Ponteiro para a nova raiz da subárvore após a inserção.
     */
    AVLnode* insertNode(AVLnode* root, int key) {
        if (root == nullptr) {
            root = new AVLnode(key);
            root->left = root->right = nullptr;
            root->height = 1;
            return root;
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

    /**
     * @brief Remove um nó com a chave especificada da árvore.
     * @param root Ponteiro para o nó raiz da subárvore onde a chave será removida.
     * @param key Valor da chave a ser removida.
     * @return Ponteiro para a nova raiz da subárvore após a remoção.
     */
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

    void inLevelOrder(AVLnode* root) {
        if (root == nullptr) {
            return;
        }

        std::queue<AVLnode*> q;
        q.push(root);

        while (!q.empty()) {
            AVLnode* current = q.front();
            q.pop();

            std::cout << current->key << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }

            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

public:
    /**
     * @brief Construtor da classe AVLTree. Inicializa a árvore vazia.
     */
    AVLTree() : root(nullptr) {}

    AVLnode* searchRecursive(int key) {
        return searchRecursive(root, key);
    }

    AVLnode* searchIterative(int key) {
        return searchIterative(root, key);
    }

    void insertNode(int key) {
        root = insertNode(root, key);
    }

    AVLnode* deleteNode(int key) {
        return deleteNode(root, key);
    }

    void print() {
        inLevelOrder(root);
    }
};