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

  /// @brief Sobe um elemento na heap a partir de sua posição.
  /// @param index Posição do elemento a ser subido.
  virtual void up(int index) = 0;
  /// @brief Desce um elemento na heap a partir de sua posição.
  /// @param index Posição do elemento a ser descido.
  virtual void down(int index) = 0;

public:
  Heap(int size)
  {
    this->size = size;
    this->heap = new node[size];
  };

  Heap(int size, node *array)
  {
    this->size = size;
    heapify(array);
  }

  virtual ~Heap() = default;

  int get_size()
  {
    return this->size;
  }

  node *get_data()
  {
    return this->heap;
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

  /// @brief Altera a prioridade (valor) de um elemento e rearranja-o na heap.
  /// @param element_priority Prioridade do elemento, usado para encontrá-lo na heap.
  /// @param new_priority Nova prioridade do elemento.
  virtual void change_priority(int element_priority, int new_priority) = 0;

  /// @brief Adiciona um elemento na heap.
  /// @param value A chave do novo elemento.
  /// @details A função primeiro aumenta o tamanho da MaxHeap e aloca o novo elemento na última posição.
  /// Assim, para que o elemento esteja na posição certa, executa-se o algoritmo para subir o elemento até a posição ideal.
  void insert(int value)
  {
    size++;
    node newNode = node(value);
    heap[size - 1] = newNode;
    up(size - 1);
  }

  /// @brief Remove o elemento raiz da heap.
  /// @details A função realiza a troca da raiz com a última folha
  /// e rearranja esta folha dentro da heap corretamente.
  void remove_root()
  {
    if (size > 0)
    {
      swap(0, size - 1);
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

  /// @brief Transforma um vetor comum em uma Max Heap.
  /// @param array Ponteiro para o vetor.
  void heapify(node *array)
  {
    heap = array;
    for (int i = (size / 2) - 1; i >= 0; i--)
    {
      down(i);
    }
  }

  /// @brief Ordena a heap de forma crescente para MaxHeap e decrescente para MinHeap.
  /// @param array Argumento opcional que representa um vetor.
  /// Se o vetor for fornecido, este será transformado em heap e ordenado após isso.
  /// Senão, será usado o armazenado anteriormente.
  /// @details Em resumo, o heapsort usa da função remove_root para trocar de lugar as raízes da árvore (números grandes para MaxHeap e pequenos para MinHeap) com as folhas (números pequenos para MinHeap e grandes para MaxHeap) e ordenar as antigas folhas na árvore. O tamanho da heap é alterado no remove_root, mas ajustado ao fim do heapsort para englobar todos os elementos.
  void sort(node *array = nullptr)
  {
    if (array != nullptr)
      heapify(array);

    if (heap == nullptr)
    {
      std::cout << "Heap is empty! Provide some data. \n";
      return;
    }

    int original_size = this->size;

    for (int i = size; i > 1; i--)
    {
      remove_root();
    }

    this->size = original_size;
  }
};

#endif // !HEAP_HPP