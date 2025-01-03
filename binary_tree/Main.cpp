#include "BinaryTree.h"
#include <iostream>
using namespace std;

int main() {
    BinaryTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Pré-ordem: ";
    tree.displayPreOrder();

    cout << "Em ordem: ";
    tree.displayInOrder();

    cout << "Pós-ordem: ";
    tree.displayPostOrder();

    cout << "Em nível: ";
    tree.displayLevelOrder();

    tree.remove(5);
    cout << "Após remover 5 (em ordem): ";
    tree.displayInOrder();

    return 0;
}
