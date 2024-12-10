#include "node.h"
#include <iostream>

/// @brief Implementação de uma heap em ordem decrescente, a MaxHeap
class Heap
{
private:
  /// @brief Ponteiro para a raiz da heap
  node *heap;
  /// @brief Quantidade de elementos que a heap comporta
  int size;

  void swap(int i1, int i2)
  {
    node aux = heap[i1];
    heap[i1] = heap[i2];
    heap[i2] = aux;
  }

  // Probably messed up
  void up(int index)
  {
    int parent = index / 2;
    if (index > 1 && heap[index].key > heap[parent].key)
    {
      swap(index, parent);
      up(parent);
    }
  }

  /// @brief Desce um elemento na heap a partir de sua posição.
  /// @param actual_element Posição do elemento a ser descido.
  void down(int actual_element)
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
  Heap(int size)
  {
    this->size = size;
    this->heap = new node[size];
  };

  virtual ~Heap() = default;

  void build(node *array)
  {
    heap = array;
    for (int i = (size / 2) - 1; i >= 0; i--)
    {
      down(i);
    }
  }

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

  void change(int index, node newValue)
  {
    if (size >= index)
    {
      heap[index] = newValue;
    }
  };

  void insert(int value)
  {
    size++;
    node newNode = node(value);
    heap[size] = newNode;
    up(size);
  }

  void remove(int value)
  {
    if (size > 0)
    {
      heap[0] = heap[size];
      size--;
      down(0);
    }
  }

  void print()
  {
    std::cout << "Here's your current Heap: \n";
    for (int i = 0; i < size; i++)
    {
      auto node = heap[i];
      std::cout << node.key << " ";
    }
  }
};
