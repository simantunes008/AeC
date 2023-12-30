#include <stdio.h>
#include <stdlib.h>

typedef struct avlnode {
    int valor;
    int bal; // 0 para equilibrada, 1 para mais pesada à direita, -1 para mais pesada à esquerda
    struct avlnode * esq;
    struct avlnode * dir;
} * AVLTree;

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
