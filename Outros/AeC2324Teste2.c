#include <stdlib.h>
#include <stdio.h>

#define H 0

// 1.
// [_,_,_,_,_,_,_,_,8,_,_]
// [_,_,_,_,_,_,_,18,8,_,_]
// [_,_,_,_,_,_,_,18,8,7,_]
// [_,_,_,_,_,_,_,18,8,7,10]
// [_,_,_,_,_,_,_,18,_,7,10]
// [_,_,_,_,_,_,_,18,29,7,10]
// [20,_,_,_,_,_,_,18,29,7,10]

// 2. a) 

// b)

int checkAVLRecursiva(int t[], int or, int N, int * alt) {
    if (or >= N || t[or] == H) {
        return 0;  // Nó nulo não contribui para a altura
    }

    int altesq, altdir;
    altesq = altdir = 0;

    int l = checkAVLRecursiva(t, 2 * or + 1, N, &altesq);
    int r = checkAVLRecursiva(t, 2 * or + 2, N, &altdir);

    if (l == -1 || r == -1 || abs(altesq - altdir) > 1) {
        return -1;  // Subárvore não é AVL
    }

    * alt = 1 + (altesq > altdir ? altesq : altdir);  // Atualiza a altura

    return 1;
}

int checkAVL(int t[], int N) {
    int h = 0;
    return checkAVLRecursiva(t, 0, N, &h) != -1;
}

int main() {
    int t[] = {5, 10, H, 20};
    if (checkAVL(t, 4)) {
        printf("É AVL\n");
    } else {
        printf("Não é AVL\n");
    }
    return 0;
}

// 3. a) e b)
// https://visualgo.net/en/dfsbfs
// Ir ao site acima, meter o grafo e confirmar.

// 4.
