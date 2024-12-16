#include "Tree.hpp"
#include "Node.hpp"

#include <iostream>


int main(int argc, char **argv){
    Tree *tree = new Tree();

    std::cout << "Insert the amount of elements to insert" << std::endl;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        std::cin >> key;
        tree->insert(key);
    }
    tree->print();
    
    std::cout << "Insert a element to find in the tree: " << std::endl;
    int key;
    std::cin >> key;
    Node *node = tree->search(key);
    if (node != nullptr) {
        std::cout << "Found: " << node->key << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }
    
    std::cout << "Insert the amount of elements to remove from the tree: " << std::endl;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int key;
        std::cin >> key;
        tree->remove(key);
    }
    tree->print();
    
    delete tree;
    return EXIT_SUCCESS;
}
