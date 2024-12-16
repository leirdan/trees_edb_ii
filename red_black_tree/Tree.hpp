#ifndef _TREE_HPP
#define _TREE_HPP

#include "Node.hpp"

#include <iostream>

/**
 * @class Tree
 * @brief A class representing a Red-Black Tree.
 */
class Tree {
    public:
        Node *root; ///< The root node of the tree.

        /**
         * @brief Constructor for the Tree class.
         */
        Tree(){
            root = nullptr;
        }

        /**
         * @brief Destructor for the Tree class.
         */
        ~Tree(){
            destroy_tree(root);
        }

        /**
         * @brief Inserts a key into the tree.
         * @param key The key to be inserted.
         */
        void insert(int key){
            Node *z = new Node(key);
            Node *y = nullptr;
            Node *x = root;
            while (x != nullptr) {
                y = x;
                if (z->key < x->key) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }
            z->parent = y;
            if (y == nullptr) {
                root = z;
            } else if (z->key < y->key) {
                y->left = z;
            } else {
                y->right = z;
            }
            z->left = nullptr;
            z->right = nullptr;
            z->color = true;
            insert_fixup(z);
        }

        /**
         * @brief Removes a key from the tree.
         * @param key The key to be removed.
         */
        void remove(int key){
            Node *z = search(key);
            if (z == nullptr) {
                return;
            }
            Node *y = z;
            bool y_original_color = y->color;
            Node *x;
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
            if (y_original_color == false) {
                remove_fixup(x);
            }
            delete z;
        }

        /**
         * @brief Searches for a key in the tree.
         * @param key The key to search for.
         * @return A pointer to the node containing the key, or nullptr if not found.
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
         * @brief Prints the tree.
         */
        void print(){
            print(root, 0);
        }
    private:

        void destroy_tree(Node *x){
            if (x != nullptr) {
                destroy_tree(x->left);
                destroy_tree(x->right);
                delete x;
            }
        }

        /**
         * @brief Fixes the tree after insertion to maintain Red-Black properties.
         * @param z The node to start fixing from.
         */
        void insert_fixup(Node *z){
            while (z->parent != nullptr && z->parent->color == true) {
                if (z->parent == z->parent->parent->left) {
                    Node *y = z->parent->parent->right;
                    if (y != nullptr && y->color == true) {
                        z->parent->color = false;
                        y->color = false;
                        z->parent->parent->color = true;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->right) {
                            z = z->parent;
                            left_rotate(z);
                        }
                        z->parent->color = false;
                        z->parent->parent->color = true;
                        right_rotate(z->parent->parent);
                    }
                } else {
                    Node *y = z->parent->parent->left;
                    if (y != nullptr && y->color == true) {
                        z->parent->color = false;
                        y->color = false;
                        z->parent->parent->color = true;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent->left) {
                            z = z->parent;
                            right_rotate(z);
                        }
                        z->parent->color = false;
                        z->parent->parent->color = true;
                        left_rotate(z->parent->parent);
                    }
                }
            }
            root->color = false;
        }

        /**
         * @brief Fixes the tree after removal to maintain Red-Black properties.
         * @param x The node to start fixing from.
         */
        void remove_fixup(Node *x){
            while (x != root && x->color == false) {
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
            x->color = false;
        }

        /**
         * @brief Performs a left rotation on the tree.
         * @param x The node to rotate around.
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
         * @brief Performs a right rotation on the tree.
         * @param x The node to rotate around.
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
         * @brief Replaces one subtree as a child of its parent with another subtree.
         * @param u The node to be replaced.
         * @param v The node to replace with.
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
         * @brief Finds the minimum node in a subtree.
         * @param x The root of the subtree.
         * @return A pointer to the minimum node.
         */
        Node *minimum(Node *x){
            while (x->left != nullptr) {
                x = x->left;
            }
            return x;
        }

        /**
         * @brief Prints the tree starting from a given node.
         * @param x The node to start printing from.
         * @param level The current level in the tree.
         */
        void print(Node *x, int level){
            if (x != nullptr) {
                print(x->right, level + 1);
                for (int i = 0; i < level; i++) {
                    std::cout << "    ";
                }
                std::cout << x->key << std::endl;
                print(x->left, level + 1);
            }
        }
};


#endif
