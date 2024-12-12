#define NODE_HPP
#ifndef NODE_HPP

public class node {
    public:
        int key;
        node *left;
        node *right;
        node *parent;
        bool color;
        node(int key);
        node(int key, node *left, node *right, node *parent, bool color);
        ~node();
}

#endif