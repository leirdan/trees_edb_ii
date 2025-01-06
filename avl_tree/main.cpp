#include <iostream>
#include "avltree.hpp"

int main(int argc, char **argv){
    AVLTree tree;
    int L[] = {15, 18, 20, 35, 32, 38, 30, 40, 32, 45, 48, 52, 60, 50};

    for (int i = 0; i < 14; i++) {
        tree.insertNode(L[i]);
    }

    std::cout << "Elementos inseridos. Imprimindo árvore...\n";
    tree.print();
    std::cout << "Finalizado.\n";

    std::cout << "\nProcure o nó com a chave 18 (busca recursiva):\n";
    tree.searchRecursive(18);

    std::cout << "\nProcure o nó com a chave 25 (busca iterativa):\n";
    tree.searchIterative(25);
}
