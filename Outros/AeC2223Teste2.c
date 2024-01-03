#include <stdio.h>
#include <stdlib.h>

typedef struct avlnode {
    int valor;
    int bal; // 0 para equilibrada, 1 para mais pesada à direita, -1 para mais pesada à esquerda
    struct avlnode * esq;
    struct avlnode * dir;
} * AVLTree;

// 1.

AVLTree buildRecursiva(int a[], int inicio, int fim, int * altura) {
    if (fim < inicio) {
        return NULL;
    }

    int meio = (inicio + fim) / 2;
    AVLTree tree = (AVLTree)malloc(sizeof(struct avlnode));
    tree -> valor = a[meio];
    tree -> bal = 0;
    tree -> esq = NULL;
    tree -> dir = NULL;
    (* altura)++;

    int altesq, altdir;
    altesq = altdir = * altura;

    tree -> esq = buildRecursiva(a, inicio, meio - 1, &altesq);
    tree -> dir = buildRecursiva(a, meio + 1, fim, &altdir);

    tree -> bal = altdir - altesq;

    return tree;
}

AVLTree build(int a[], int N) {
    int h = 0;
    return buildRecursiva(a, 0, N - 1, &h);
}

/**
 * A função executa em tempo linear uma vez que visitamos cada elemento do array apenas uma vez e cada chamada o número de operações é constante.
*/

// 2.

/**
 * Para ambos os casos o array de tamanho N será sempre percorrido até ao fim.
 * M.C. -> O array só tem 0s então só são realizadas N comparações.
 * P.C. -> O array tem apenas um 1 então para além das N comparações temos de chamar a função g (N + 2^N).
 * A probabilidade do array ter apenas um 1 é de N/(2^N).
 * C.M. -> N + N
*/

// 3. 

void swap(int a[], int x, int y) {
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
    return;
}

int decrease(int x, int y, int h[], int N) {
    int i = 0;
    while (h[i] != x) {
        i++;
    }
    h[i] = y;

    int pai = (i - 1) / 2;
    
    while (i > 0 && h[pai] > h[i]) {
        swap(h, i, pai);
        i = pai;
        pai = (i - 1) / 2;
    }
    return 1;
}

/**
 * M.C. -> O elemento a ser substituído está na raiz da heap. Como x < y só precisamos de executar apenas uma troca (O(1)).
 * P.C- -> O elemento a ser substituído está numa folha e tem de ir para a raiz da heap (O(log N)).
*/

// 4.
