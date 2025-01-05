# Definição do pseudocódigo do HeapSort

```none
# Função que desce um elemento em uma posição X na heap de acordo com o valor de seus filhos.
# Ao final, caso o elemento tenha sido descido, o algoritmo é chamado recursivamente,
# levando em conta os novos filhos do elemento.
# NOTA: algoritmo criado para a MinHeap. 
# Caso deseje adaptar para a MaxHeap, basta 
# trocar o sinal de comparação das linhas "tem filho esquerdo" e "direito" para ">".
descer(heap[], tamanho, indice_atual): 
  # Não há mais o que descer
  se (indice == tamanho)
    retorne
    
  # Atribuição de variáveis para melhorar a leitura
  seja indice_a_trocar = indice_atual 

  seja tem_filho_esquerdo = indice_atual * 2 < tamanho
  seja tem_filho_direito = indice_atual * 2 + 1 < tamanho
  
  seja pai = heap[indice_atual]
  seja filho_esquerdo = se (tem_filho_esquerdo): heap[indice_atual * 2] senao: nulo
  seja filho_direito = se (tem_filho_direito): heap[indice_atual * 2 + 1] senao: nulo 
    
  se (tem_filho_esquerdo && pai < filho_esquerdo):
    indice_a_trocar = indice_atual * 2
    
  se (tem_filho_direito && pai < filho_direito):
    indice_a_trocar = indice_atual * 2 + 1
    
  # Se o índice de troca não foi atualizado para um dos filhos, 
  # quer dizer que o elemento já está no local certo e não há motivo para trocar.
  seja deve_trocar = indice_a_trocar != indice_atual
  
  se (deve_trocar):
    troca(heap, indice_atual, indice_a_trocar)
    descer(heap, tamanho, indice_a_trocar)

  retorne


# Função que transforma um array qualquer em uma heap.
heapify(array[], tamanho):
  # O loop inicia da metade da lista para dar mais
  # chances que o elemento tenha filhos.
  para (indice = tamanho / 2; indice > 1; indice--)
    descer(array, indice)
    
# Função que elimina a raiz da heap, trocando com o último elemento desta e rearranjando-o. 
# NOTA: pode e deve ser usada em conjunto com a função de "heapsort".
remover_raiz(heap[], tamanho):
  # Se tamanho da heap é 1, há somente a raiz.
  se (tamanho == 1)
    retorne
    
  # Troca o primeiro com o último elemento de posição
  troca(heap, 1, tamanho)

  # Desce o primeiro elemento, que anteriormente estava ao fim da lista, 
  # para sua posição apropriada.
  descer(heap, 1)

heapsort(heap[], tamanho): 
  # Se tamanho da heap é 1, não há o que ordenar.
  se (tamanho == 1) 
    retorne

  # Constrói uma heap a partir do vetor original.
  heapify(heap)
    
  # Por meio desta iteração, vai-se criando uma divisão na heap, 
  # entre a seção não-ordenada (que a princípio é todo o vetor)
  # e a ordenada (que começa não tendo elementos e vai expandindo-se gradativamente). 
  # Ao final do loop, toda a heap estará ordenada.
  para (seja indice = tamanho; indice > 1; indice--):
    remover_raiz(heap, indice)
    
  retorne
```
