#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "heap.hpp"

/// @brief Implementação de uma heap em ordem decrescente, a MaxHeap
class MaxHeap : public Heap
{
private:
  void up(int index) override
  {
    if (index > 0)
    {
      int parent = get_parent(index);
      // Troca os elementos de posição se a chave do pai for menor que a do filho
      if (heap[parent].key < heap[index].key)
      {
        swap(parent, index);
        up(parent);
      }
    }
  }

  void down(int actual_element) override
  {
    int bigger_index = actual_element;
    int left_c = get_left_child(actual_element);
    int right_c = get_right_child(actual_element);

    // Checa se o filho da esquerda é maior que o pai
    if (left_c < size && heap[left_c].key > heap[bigger_index].key)
    {
      bigger_index = left_c;
    }

    // Checa se o filho da direita é maior que o pai
    if (right_c < size && heap[right_c].key > heap[bigger_index].key)
    {
      bigger_index = right_c;
    }

    // Garante que o índice foi alterado
    if (bigger_index != actual_element)
    {
      swap(bigger_index, actual_element);
      down(bigger_index);
    }
  };

public:
  MaxHeap(int size) : Heap(size) {};

  virtual ~MaxHeap() = default;
};

#endif // !MAX_HEAP_HPP