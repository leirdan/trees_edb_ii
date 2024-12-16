#ifndef _TREE_HPP
#define _TREE_HPP

#include "Node.hpp"

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
        Tree();

        /**
         * @brief Destructor for the Tree class.
         */
        ~Tree();

        /**
         * @brief Inserts a key into the tree.
         * @param key The key to be inserted.
         */
        void insert(int key);

        /**
         * @brief Removes a key from the tree.
         * @param key The key to be removed.
         */
        void remove(int key);

        /**
         * @brief Searches for a key in the tree.
         * @param key The key to search for.
         * @return A pointer to the node containing the key, or nullptr if not found.
         */
        Node *search(int key);

         /**
         * @brief Prints the tree.
         */
        void print();
    private:

        void destroy_tree(Node *x);

        /**
         * @brief Fixes the tree after insertion to maintain Red-Black properties.
         * @param z The node to start fixing from.
         */
        void insert_fixup(Node *z);

        /**
         * @brief Fixes the tree after removal to maintain Red-Black properties.
         * @param x The node to start fixing from.
         */
        void remove_fixup(Node *x);

        /**
         * @brief Performs a left rotation on the tree.
         * @param x The node to rotate around.
         */
        void left_rotate(Node *x);

        /**
         * @brief Performs a right rotation on the tree.
         * @param x The node to rotate around.
         */
        void right_rotate(Node *x);

        /**
         * @brief Replaces one subtree as a child of its parent with another subtree.
         * @param u The node to be replaced.
         * @param v The node to replace with.
         */
        void transplant(Node *u, Node *v);

         /**
         * @brief Finds the minimum node in a subtree.
         * @param x The root of the subtree.
         * @return A pointer to the minimum node.
         */
        Node *minimum(Node *x);

        /**
         * @brief Prints the tree starting from a given node.
         * @param x The node to start printing from.
         * @param level The current level in the tree.
         */
        void print(Node *x, int level);
};


#endif
