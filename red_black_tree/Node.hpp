#ifndef NODE_HPP
#define NODE_HPP


/**
 * @class Node
 * @brief A class representing a node in a Red-Black Tree.
 */
class Node {
    public:
        int key; ///< The key of the node.
        Node *left; ///< Pointer to the left child.
        Node *right; ///< Pointer to the right child.
        Node *parent; ///< Pointer to the parent node.
        bool color; ///< The color of the node (0 = black, 1 = red).
        
        /**
         * @brief Constructor for the Node class.
         * @param key The key of the node.
         */
        Node(int key){
            this->key = key;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            color = false;
        }

        /**
         * @brief Constructor for the Node class with all parameters.
         * @param key The key of the node.
         * @param left Pointer to the left child.
         * @param right Pointer to the right child.
         * @param parent Pointer to the parent node.
         * @param color The color of the node.
         */
        Node(int key, Node *left, Node *right, Node *parent, bool color){
            this->key = key;
            this->left = left;
            this->right = right;
            this->parent = parent;
            this->color = color;
        }

        /**
         * @brief Destructor for the Node class.
         */
        ~Node(){
            delete left;
            delete right;
        }
};

#endif