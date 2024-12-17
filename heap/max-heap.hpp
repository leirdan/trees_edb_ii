#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include "heap.hpp"

/// @brief Implementação de uma heap em ordem decrescente, a MaxHeap
class MaxHeap : Heap
{
private:
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
  MaxHeap(int size) : Heap(size) {};

  virtual ~MaxHeap() = default;

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

  /// @brief Ordena a heap de forma crescente.
  /// @param array Argumento opcional que representa um vetor.
  /// Se o vetor for fornecido, este será transformado em heap e ordenado após isso.
  /// Senão, será usado o armazenado anteriormente.
  /// @details Em resumo, o heapsort usa da função remove_root para trocar de lugar as raízes da árvore (números grandes) com as folhas (números pequenos) e rearranjar estes. Logo, os maiores sempre ficarão ao fim e os menores no começo, formando uma lista crescente. O tamanho da heap é alterado no remove_root, mas ajustado ao fim do heapsort para englobar todos os elementos
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