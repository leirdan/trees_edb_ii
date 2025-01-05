#ifndef MIN_HEAP_CPP
#define MIN_HEAP_CPP

#include "heap.hpp"

/// @brief Implementação de uma heap em ordem crescente, a MinHeap
class MinHeap : public Heap
{
private:
  void up(int index) override
  {
    if (index > 0)
    {
      int parent = get_parent(index);
      if (heap[parent].key > heap[index].key)
      {
        swap(parent, index);
        up(parent);
      }
    }
  }

  void down(int actual_element) override
  {
    int smaller_index = actual_element;
    int left_c = get_left_child(actual_element);
    int right_c = get_right_child(actual_element);

    // Checa se o filho da esquerda é menor que o pai
    if (left_c < size && heap[left_c].key < heap[smaller_index].key)
    {
      smaller_index = left_c;
    }

    // Checa se o filho da direita é menor que o pai
    if (right_c < size && heap[right_c].key < heap[smaller_index].key)
    {
      smaller_index = right_c;
    }

    // Garante que o índice foi alterado
    if (smaller_index != actual_element)
    {
      swap(smaller_index, actual_element);
      down(smaller_index);
    }
  }

public:
  MinHeap(int size) : Heap(size) {};

  virtual ~MinHeap() = default;
};
#endif // !MIN_HEAP_CPP