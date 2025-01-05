#ifndef NODE_H
#define NODE_H

/// @brief Nó da Heap.
/// @details Bastante simples. O campo "key" representa tanto o valor quanto a prioridade
/// do nó em relação aos demais. Como representamos conjuntos de inteiros, não houve
/// a necessidade da criação de um campo "priority", mas para outros tipos haveria a necessidade.
struct node
{
  /// @brief Valor do nó.
  int key;

  node()
  {
    this->key = 0;
  }

  node(int key)
  {
    this->key = key;
  }
};

#endif