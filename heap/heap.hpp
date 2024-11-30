#include "node.h"

class Heap
{
private:
  node *heap;
  int size;

  void swap(int i1, int i2)
  {
    node aux = heap[i1];
    heap[i1] = heap[i2];
    heap[i2] = aux;
  }

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
  /// @param index Posição do elemento a ser descido.
  void down(int index)
  {
    int bigger = index;

    if (size >= 2 * index && heap[bigger].key <= heap[2 * index].key)
    {
      bigger = 2 * index;
    }

    if (size >= 2 * index + 1 && heap[bigger].key <= heap[2 * index + 1].key)
    {
      bigger = 2 * index + 1;
    }

    // Garante que o índice foi alterado
    if (bigger != index)
    {
      swap(bigger, index);
      down(bigger);
    }
  };

public:
  Heap(int size)
  {
    this->size = size;
    this->heap = new node[size];
  };

  virtual ~Heap() = default;

  void build(int array[]) {}

  node get(int index)
  {
    return heap[index];
  }

  node get_parent(int childIndex)
  {
    if (size >= childIndex)
      return heap[childIndex / 2];
  }

  node get_left_child(int parentIndex)
  {
    if (size >= parentIndex * 2)
      return heap[parentIndex * 2];
  }

  node get_right_child(int parentIndex)
  {
    if (size >= parentIndex * 2 + 1)
      return heap[parentIndex * 2 + 1];
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
};
