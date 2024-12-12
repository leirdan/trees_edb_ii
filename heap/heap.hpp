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

  /// @brief Sobe um elemento na heap a partir de sua posição.
  /// @param index Posição do elemento a ser subido.
  void up(int index)
  {
    int parent = get_parent(index);
    // Só troca elementos caso a chave do filho seja maior que o do pai.
    if (index > 0 && heap[index].key > heap[parent].key)
    {
      swap(index, parent);
      up(parent); // Executa o algoritmo recursivamente para verificar se o elemento não precisa ser subido novamente.
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

  /// @brief Adiciona um elemento na heap.
  /// @param value A chave do novo elemento.
  /// @details A função primeiro aumenta o tamanho da Heap e aloca o novo elemento na última posição.
  /// Assim, para que o elemento esteja na posição certa, executa-se o algoritmo para subir o elemento até a posição ideal.
  void insert(int value)
  {
    size++;
    node newNode = node(value);
    heap[size - 1] = newNode;
    up(size - 1);
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
    std::cout << "\n";
  }
};
