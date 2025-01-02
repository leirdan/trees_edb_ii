#ifndef NODE_HPP
#define NODE_HPP


/**
 * @class Node
 * @brief A class representing a node in a Red-Black Tree.
 */
class Node {
    public:
        int key; ///< Chave do nó.
        Node *left; ///< Ponteiro para o filho esquerdo.
        Node *right; ///< Ponteiro para o filho direito.
        Node *parent; ///< Ponteiro para o pai.
        bool color; ///< Cor do nó (0 = negro, 1 = vermelho).
        int depth; ///< Nivel do nó.
        
        /**
         * @brief Construtor da classe Node.
         * @param key A chave do nó.
         */
        Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(true), depth(0) {}

        /**
         * @brief Destruidor da classe Node.
         */
        ~Node() = default;
};

#endif