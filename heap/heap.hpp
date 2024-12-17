#ifndef HEAP_HPP
#define HEAP_HPP

#include "node.h"
#include <iostream>

class Heap
{
protected:
  /// @brief Ponteiro para a raiz da heap
  node *heap;
  /// @brief Quantidade de elementos que a heap comporta
  int size;

  /// @brief Função auxiliar para trocar elementos.
  /// @param i1 Índice do 1º elemento
  /// @param i2 Índice do 2º elemento
  void swap(int i1, int i2)
  {
    node aux = heap[i1];
    heap[i1] = heap[i2];
    heap[i2] = aux;
  }
  virtual void up(int index) = 0;
  virtual void down(int index) = 0;

public:
  Heap(int size)
  {
    this->size = size;
    this->heap = new node[size];
  };

  virtual ~Heap() = default;

  int get_parent(int childIndex)
  {
    return (childIndex - 1) / 2;
  }

  int get_left_child(int parentIndex)
  {
    return parentIndex * 2 + 1;
  }

  int get_right_child(int parentIndex)
  {
    return parentIndex * 2 + 2;
  }

  void print()
  {
    std::cout << "Here's your current Heap: \n";
    for (int i = 0; i < size; i++)
    {
      auto node = heap[i];
      std::cout << node.key << " ";
    }
    std::cout << "\n";
  }
};

#endif // !HEAP_HPP