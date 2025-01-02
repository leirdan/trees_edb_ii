#include "Tree.hpp"
#include "Node.hpp"

#include <iostream>


int main(int argc, char **argv){
    Tree *tree = new Tree();

    std::cout << "Insira a quantidade de elementos a serem inseridos na árvore: ";
    int n;
    std::cin >> n;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Insira o elemento a ser inserido na árvore: ";
        int key;
        std::cin >> key;
        std::cout << std::endl;
        tree->insert(key);
        tree->print();
        std::cout << std::endl;
    }

    std::cout << "Árvore pós inserções: " << std::endl;
    tree->print();
    
    std::cout << std::endl;
    std::cout << "Insira um elemento a ser encontrado na árvore: ";
    int key;
    std::cin >> key;
    Node *node = tree->search(key);
    if (node != nullptr) {
        std::cout << "Encontrado: " << node->key << " nivel: " << node->depth << " cor: " << node->color << std::endl;
    } else {
        std::cout << "Não Encontrado." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Insira o número de elementos a serem removidos: ";
    std::cin >> n;
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Insira um elemento para remover da árvore: ";
        int key;
        std::cin >> key;
        std::cout << std::endl;
        tree->remove(key);
        tree->print();
        std::cout << std::endl;
    }

    std::cout << "Árvore pós remoções: " << std::endl;
    tree->print();

    delete tree;
    return EXIT_SUCCESS;
}
