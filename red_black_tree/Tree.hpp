#ifndef _TREE_HPP
#define _TREE_HPP

#include "Node.hpp"

#include <iostream>
#include <iomanip>

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
            Node *newNode = new Node(key);
            newNode->color = true;
            newNode->parent = nullptr;
            newNode->right = nullptr;
            newNode->left = nullptr;
            
            // If the tree is empty, the new node becomes the root.
            if (root == nullptr) {
                root = newNode;
                newNode->color = false;
                newNode->depth = 0;
                return;
            }

            // Find the parent of the new node.
            Node *current = root;
            Node *parent = nullptr;
            int depth = 0;
            while(current != nullptr) {
                parent = current;
                if (newNode->key < current->key) {
                    current = current->left;
                } else {
                    current = current->right;
                }
                depth++;
            }
            newNode->parent = parent;
            newNode->depth = depth;
            
            // If the new node is less than the parent, it becomes the left child.
            if (newNode->key < parent->key) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }

            insert_fixup(newNode);
        }

        /**
         * @brief Removes a key from the tree.
         * @param key The key to be removed.
         */
        void remove(int key){
            Node *z = search(key);
            if (z == nullptr) {
                std::cout << "Key not found in the tree." << std::endl;
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
            if (y_original_color == false) {
                remove_fixup(x);
            }
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

        /**
         * @brief Tree destructor
         */
        void destroy_tree(Node *x){
            if (x != nullptr) {
                destroy_tree(x->left);
                destroy_tree(x->right);
                delete x;
            }
        }

        void insert_fixup(Node *z) {
            while (z->parent != nullptr && z->parent->color == true) {
                Node *grandparent = z->parent->parent;

                // case 1: z's parent is the left child of the grandparent
                if (z->parent == grandparent->left) { 
                    Node *uncle = grandparent->right;

                    // case 1: uncle is red
                    if (uncle != nullptr && uncle->color == true) { 
                        z->parent->color = false;
                        uncle->color = false;
                        grandparent->color = true;
                        z = grandparent;
                    } 
                    // case 2: uncle is black
                    else { 
                        if (z == z->parent->right) {
                            z = z->parent;
                            left_rotate(z);
                        }
                        // Case 3: z is left child
                        z->parent->color = false;
                        grandparent->color = true;
                        right_rotate(grandparent);
                    }
                }
                // case 2: z's parent is the right child of the grandparent
                else { 
                    Node *uncle = grandparent->left;

                    // case 1: uncle is red
                    if (uncle != nullptr && uncle->color == true) { 
                    z->parent->color = false;
                    uncle->color = false;
                    grandparent->color = true;
                    z = grandparent;
                    } 
                    
                    else {
                        // case 2: z is left child
                        if (z == z->parent->left) { 
                            z = z->parent;
                            right_rotate(z);
                        }
                        // case 3: z is right child
                        else { z->parent->color = false;
                        grandparent->color = true;
                        left_rotate(grandparent);
                        }
                    }
                }
            }

            // Make sure the root is black
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
