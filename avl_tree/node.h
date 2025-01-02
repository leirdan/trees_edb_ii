#ifndef NODE_H
#define NODE_H

struct AVLnode {
    int key;
    int height;
    AVLnode* left;
    AVLnode* right;

    // Constructor
    AVLnode(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

#endif // NODE_H
