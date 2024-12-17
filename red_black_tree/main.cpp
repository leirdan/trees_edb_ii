#include "Tree.hpp"
#include "Node.hpp"

#include <iostream>


int main(int argc, char **argv){
    Tree *tree = new Tree();

    std::cout << "Insert the amount of elements to insert" << std::endl;
    int n;
    std::cin >> n;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Insert a element to insert in the tree: " << std::endl;
        int key;
        std::cin >> key;
        std::cout << std::endl;
        tree->insert(key);
        tree->updateNodeProperties();
        //tree->print();
        std::cout << std::endl;
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
    std::cout << std::endl;

    std::cout << "Insert the amount of elements to remove from the tree: " << std::endl;
    std::cin >> n;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Insert a element to remove from the tree: " << std::endl;
        int key;
        std::cin >> key;
        std::cout << std::endl;
        tree->remove(key);
        tree->updateNodeProperties();
        //tree->print();
        std::cout << std::endl;
    }
    

    delete tree;
    return EXIT_SUCCESS;
}
