#ifndef HEAP_H
#define HEAP_H

/**
 * @struct pQueue
 * @brief Estrutura para representar uma lista de espera.
 */
typedef struct pQueue PriorityQueue;


/**
 * @brief Puxa o elemento que está na posição i da min-heap h até que satisfaça a propriedade das min-heaps.
 *
 * @param i
 * @param h
 * @return void.
 */
void bubbleUp(int i, int h[]);

/**
 * @brief Empura o elemento que está na posição i da min-heap h até que satisfaça a propriedade das min-heaps.
 *
 * @param i
 * @param h
 * @param size
 * @return void.
 */
void bubbleDown(int i, int h[], int size);

/**
 * @brief Inicializa q com a fila vazia.
 *
 * @param q
 * @return void.
 */
void empty(PriorityQueue * q);

/**
 * @brief Testa se a lista q está vazia.
 *
 * @param q
 * @return 1 se q estiver vazia e 0 em caso contrário.
 */
int isEmpty(PriorityQueue * q);

/**
 * @brief Adiciona um elemento à fila.
 *
 * @param q
 * @param x
 * @return 0 se for possível adicionar e 1 em caso contrário.
 */
int add(int x, PriorityQueue * q);

/**
 * @brief Remove o próximo elemento (devolvendo-o em * rem)
 *
 * @param q
 * @param rem
 * @return 0 se for possível remover e 1 em caso contrário.
 */
int myremove(PriorityQueue * q, int * rem);

/**
 * @brief Obtém uma permutação do array que seja uma min-heap através de sucessivos bubbleUp's.
 *
 * @param v
 * @param N
 * @return void.
 */
void heapify_top_down(int v[], int N);

/**
 * @brief Obtém uma permutação do array que seja uma min-heap através de sucessivos bubbleDown's.
 *
 * @param v
 * @param N
 * @return void.
 */
void heapify_bottom_up(int v[], int N);

/**
 * @brief Usando a função bubbleDown definida acima, transforma a min-heap h, num array ordenado por ordem decrescente.
 *
 * @param h
 * @param N
 * @return void.
 */
void ordenaHeap(int h[], int N);

#endif
