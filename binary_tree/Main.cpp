#include "BinaryTree.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    BinaryTree tree;
    vector<int> data = {10, 20, 30, 40, 50, 60, 70};

    // Construção da árvore balanceada
    tree.buildTree(data);

    // Exibição da árvore
    cout << "Pré-ordem: ";
    tree.displayPreOrder();

    cout << "Em ordem: ";
    tree.displayInOrder();

    cout << "Pós-ordem: ";
    tree.displayPostOrder();

    cout << "Em nível: ";
    tree.displayLevelOrder();

    // Inserção de novos elementos
    cout << "Inserindo 25 na árvore..." << endl;
    tree.insert(25);

    cout << "Após inserção de 25 (Pré-ordem): ";
    tree.displayPreOrder();

    // Busca de um elemento
    int searchValue = 30;
    cout << "Buscando o valor " << searchValue << " na árvore..." << endl;
    if (tree.search(searchValue)) {
        cout << "Valor " << searchValue << " encontrado na árvore!" << endl;
    } else {
        cout << "Valor " << searchValue << " não encontrado na árvore." << endl;
    }

    // Remoção de um elemento
    int removeValue = 40;
    cout << "Removendo o valor " << removeValue << " da árvore..." << endl;
    tree.remove(removeValue);

    cout << "Após remoção de " << removeValue << " (Pré-ordem): ";
    tree.displayPreOrder();

    return 0;
}
