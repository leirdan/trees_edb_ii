# Definição do pseudocódigo do HeapSort

```none
TODO: descrever a função descer!!


# Função que transforma um array qualquer em uma heap.
heapify(array[], tamanho):
  # Começa da metade da lista.
  # O algoritmo 'descer' vai trocar de posição o elemento e seus filhos se necessário a cada    
  # iteração, transformando a lista inteira em uma heap gradativamente. 
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

  # Desce o primeiro elemento, que anteriormente estava ao fim da lista, para sua posição apropriada.
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
  para (indice = tamanho; indice > 1; indice--):
    remover_raiz(heap, indice)
    
  retorne
```
