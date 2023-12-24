#include <stdio.h>
#include <stdlib.h>

#include <heap.h>

#define pai(i) ((i - 1) / 2)
#define esquerda(i) (2 * (i) + 1)
#define direita(i) (2 * (i) + 2)

#define Max 100

typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

void swap(int * a, int * b) {
    int temp = * a;
    * a = * b;
    * b = temp;
}

// 2.

void bubbleUp(int i, int h[]) {
    int pai = pai(i);

    while (i && h[i] < h[pai]) {
        swap(&h[i], &h[pai]);
        i = pai;
        pai = pai(i);
    }
}

// P.C. -> O elemento está no último nível da min-heap e tem de ir para a raiz - O(log n)


// 3.

void bubbleDown(int i, int h[], int size) {
    while (esquerda(i) < size) {
        int min = esquerda(i);

        if (direita(i) < size && h[direita(i)] < h[min]) {
            min = direita(i);
        } 

        if (h[i] > h[min]) {
            swap(&h[i], &h[min]);
            i = min;
        } else {
            break;
        }
    }
}

// P.C. -> O elemento está na raiz da min-heap e tem de ir para o último nível - O(log n)


// 4. a)

void empty(PriorityQueue * q) {
    q -> tamanho = 0;
}

// b)

int isEmpty(PriorityQueue * q) {
    return (q -> tamanho == 0);
}

// c)

int add(int x, PriorityQueue * q) {
    if (q -> tamanho + 1 >= Max) {
        return 1;
    }
    q -> valores[q -> tamanho] = x;
    bubbleUp(q -> tamanho, q -> valores);
    q -> tamanho++;
    return 0;
}

// d)

int myremove(PriorityQueue * q, int * rem) {
    if (isEmpty(q)) {
        return 1;
    }
    * rem = q -> valores[0];
    q -> tamanho--;
    q -> valores[0] = q -> valores[q -> tamanho];
    bubbleDown(0, q -> valores, q -> tamanho);
    return 0;
}

// 5.

void heapify_top_down(int v[], int N) {
    for (int i = 1; i < N; i++) {
        bubbleUp(i, v);
    }
}

void heapify_bottom_up(int v[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) {
        bubbleDown(i, v, N);
    }
}

// 6.

void ordenaHeap(int h[], int N) {
    for (int i = N - 1; i >= 0; i--) {
        swap(&h[0], &h[i]);
        bubbleDown(0, h, i);
    }
}

/* 
7.  P.C. -> Os k maiores elementos estão no final da sequência. 
    Para cada inserção na heap à um custo de O(log k)
    N - k inserções -> O((N - k) * log k) 
*/
