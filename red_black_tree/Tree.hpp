#ifndef _TREE_HPP
#define _TREE_HPP

#include "Node.hpp"

#include <iostream>
#include <iomanip>

/**
 * @class Tree
 * @brief Uma classe que representa a árvore rubro negro.
 */
class Tree {
    public:
        Node *root; ///< A raíz da árvore.

        /**
         * @brief Construtor da classe.
         */
        Tree(){
            root = nullptr;
        }

        /**
         * @brief Destruidor da classe
         */
        ~Tree(){
            destroy_tree(root);
        }

        /**
         * @brief Insere uma chave na árvore.
         * @param key A chave a ser inserida.
         */
        void insert(int key){
            Node *newNode = new Node(key);
            newNode->color = true;
            newNode->parent = nullptr;
            newNode->right = nullptr;
            newNode->left = nullptr;
            
            // Se a árvore estiver vazia, o novo nó é a raiz.
            if (root == nullptr) {
                root = newNode;
                newNode->color = false;
                newNode->depth = 0;
                return;
            }

            Node *oldNode = search(key);
            if (oldNode != nullptr) {
                std::cout << "Chave já existe." << std::endl;
                std::cout << std::endl;
                return;
            }

            // Encontra o pai do novo nó.
            Node *current = root;
            Node *parent = nullptr;
            int level = 0;
            while(current != nullptr) {
                parent = current;
                if (newNode->key < current->key) {
                    current = current->left;
                } else {
                    current = current->right;
                }
                level++;
            }
            newNode->parent = parent;
            newNode->depth = level;
            
            // Se a chave do novo nó for menor que a chave do pai, o novo nó é filho esquerdo.
            if (newNode->key < parent->key) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }

            insert_fixup(newNode);
        }

        /**
         * @brief Remove uma chave da árvore.
         * @param key A chave a ser removida.
         */
        void remove(int key){
            Node *z = search(key);
            if (z == nullptr) {
                std::cout << "Chave não encontrada." << std::endl;
                return;
            }

            Node *y = z;
            Node *x;
            bool y_original_color = y->color;

            if (z->left == nullptr) {
                x = z->right;
                transplant(z, z->right);
            } else if (z->right == nullptr) {
                x = z->left;
                transplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    if (x != nullptr) {
                        x->parent = y;
                    }
                } else {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (y_original_color == false && x != nullptr) {
                remove_fixup(x);
            }
        }

        /**
         * @brief Procura por uma chave na árvore.
         * @param key A chave a ser procurada.
         * @return O nó com a chave procurada.
         */
        Node *search(int key){
            Node *x = root;
            while (x != nullptr && x->key != key) {
                if (key < x->key) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }
            return x;
        }

         /**
         * @brief Imprime a árvore.
         */
        void print(){
            print(root, 0);
        }

    private:

        /**
         * @brief Destruidir da árvore.
         * @param x O nó a ser destruído.
         */
        void destroy_tree(Node *x){
            if (x != nullptr) {
                destroy_tree(x->left);
                destroy_tree(x->right);
                delete x;
            }
        }

        /**
         * @brief Conserta a árvore após a inserção de um nó.
         * @param z O nó a ser consertado.
         */
        void insert_fixup(Node *z) {
            while (z->parent != nullptr && z->parent->color == true) {
                Node *grandparent = z->parent->parent;

                // caso 1: o pai de z é o filho esquerdo do avô
                if (z->parent == grandparent->left) { 
                    Node *uncle = grandparent->right;

                    // caso 1: tio é vermelho
                    if (uncle != nullptr && uncle->color == true) { 
                        z->parent->color = false;
                        uncle->color = false;
                        grandparent->color = true;
                        z = grandparent;
                    } 
                    // caso 2: tio é negro
                    else { 
                        if (z == z->parent->right) {
                            z = z->parent;
                            left_rotate(z);
                        }
                        // caso 3: z é filho esquerdo
                        z->parent->color = false;
                        grandparent->color = true;
                        right_rotate(grandparent);
                    }
                }
                // caso 2: o pai de z é o filho direito do avô
                else { 
                    Node *uncle = grandparent->left;

                    // caso 1: tio é vermelho
                    if (uncle != nullptr && uncle->color == true) { 
                    z->parent->color = false;
                    uncle->color = false;
                    grandparent->color = true;
                    z = grandparent;
                    } 
                    
                    else {
                        // caso 2: z é filho esquerdo
                        if (z == z->parent->left) { 
                            z = z->parent;
                            right_rotate(z);
                        }
                        // caso 3: z é filho direito
                        else { z->parent->color = false;
                        grandparent->color = true;
                        left_rotate(grandparent);
                        }
                    }
                }
            }

            // Garatindo que a raiz seja negra
            root->color = false;
            update_depth(root, 0);
        }

        /**
         * @brief Atualiza a profundidade dos nós da árvore.
         * @param node O nó a ser atualizado.
         * @param depth A profundidade do nó.
         */
        void update_depth(Node *node, int depth) {
            if (node != nullptr) {
                node->depth = depth;
                update_depth(node->left, depth + 1);
                update_depth(node->right, depth + 1);
            }
        }

        /**
         * @brief Conserta a árvore após a remoção de um nó.
         * @param x O nó a ser consertado.
         */
        void remove_fixup(Node *x){
            while (x != root && x != nullptr && x->color == false) {
                if (x == x->parent->left) {
                    Node *w = x->parent->right;
                    if (w->color == true) {
                        w->color = false;
                        x->parent->color = true;
                        left_rotate(x->parent);
                        w = x->parent->right;
                    }
                    if ((w->left == nullptr || w->left->color == false) && (w->right == nullptr || w->right->color == false)) {
                        w->color = true;
                        x = x->parent;
                    } else {
                        if (w->right == nullptr || w->right->color == false) {
                            if (w->left != nullptr) {
                                w->left->color = false;
                            }
                            w->color = true;
                            right_rotate(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        if (w->right != nullptr) {
                            w->right->color = false;
                        }
                        left_rotate(x->parent);
                        x = root;
                    }
                } else {
                    Node *w = x->parent->left;
                    if (w->color == true) {
                        w->color = false;
                        x->parent->color = true;
                        right_rotate(x->parent);
                        w = x->parent->left;
                    }
                    if ((w->right == nullptr || w->right->color == false) && (w->left == nullptr || w->left->color == false)) {
                        w->color = true;
                        x = x->parent;
                    } else {
                        if (w->left == nullptr || w->left->color == false) {
                            if (w->right != nullptr) {
                                w->right->color = false;
                            }
                            w->color = true;
                            left_rotate(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = false;
                        if (w->left != nullptr) {
                            w->left->color = false;
                        }
                        right_rotate(x->parent);
                        x = root;
                    }
                }
            }
            if (x != nullptr) {
                x->color = false;
            }
            update_depth(root, 0);
        }

        /**
         * @brief Produz a rotação à esquerda na árvore.
         * @param x O nó a ser rotacionado.
         */
        void left_rotate(Node *x){
            Node *y = x->right;
            x->right = y->left;
            if (y->left != nullptr) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        /**
         * @brief Produz a rotação à direita na árvore.
         * @param x O nó a ser rotacionado.
         */
        void right_rotate(Node *x){
            Node *y = x->left;
            x->left = y->right;
            if (y->right != nullptr) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y;
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }

        /**
         * @brief Substitui um nó por outro.
         * @param u O nó a ser substituído.
         * @param v O nó que substituirá u.
         */
        void transplant(Node *u, Node *v){
            if (u->parent == nullptr) {
                root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            if (v != nullptr) {
                v->parent = u->parent;
            }
        }

         /**
         * @brief Encontra o nó com a menor chave na subárvore.
         * @param x O nó a partir do qual a busca deve começar.
         * @return O nó com a menor chave.
         */
        Node *minimum(Node *x){
            while (x->left != nullptr) {
                x = x->left;
            }
            return x;
        }

        /**
         * @brief Imprime a árvore.
         * @param x O nó a ser impresso.
         * @param level O nível do nó.
         */
        void print(Node *node, int level){
            if (node != nullptr) {
                if (node->right) {
                    print(node->right, level + 4);
                }
                if (level) {
                    std::cout << std::setw(level) << ' ';
                }
                if (node->right) std::cout << " /\n" << std::setw(level) << ' ';
                std::cout << node->key << (node->color ? "R" : "B") << node->depth <<"\n ";
                if (node->left) {
                    std::cout << std::setw(level) << ' ' << " \\\n";
                    print(node->left, level + 4);
                }
            }
        }
        
};


#endif
