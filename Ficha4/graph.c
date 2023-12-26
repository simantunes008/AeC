#include <stdio.h>
#include <stdlib.h>

#define NV 10

typedef struct aresta {
    int dest; 
    int custo;
    struct aresta * prox;
} * LAdj, * GrafoL [NV];

typedef int GrafoM [NV][NV];

void imprimeListaAdj(GrafoL g) {
    for (int i = 0; i < NV; i++) {
        printf("%d: ", i);
        LAdj atual = g[i];
        while (atual != NULL) {
            printf("(%d, %d) ", atual -> dest, atual -> custo);
            atual = atual -> prox;
        }
        printf("\n");
    }
}

// Representações

// 1.

void fromMat (GrafoM in, GrafoL out) {
    for (int i = 0; i < NV; i++) {
        out[i] = NULL;
        for (int j = NV - 1; j >= 0; j--) {
            if (in[i][j] != 0) {
                LAdj novo = malloc(sizeof(struct aresta));
                novo -> dest = j;
                novo -> custo = in[i][j];
                if (out[i] == NULL) {
                    novo -> prox = NULL;
                } else {
                    novo -> prox = out[i];
                }
                out[i] = novo;
            }
        }
    }
}

// 2.

void inverte(GrafoL in, GrafoL out) {
    for (int i = 0; i < NV; i++) {
        out[i] = NULL;
    }

    for (int i = 0; i < NV; i++) {
        LAdj atual = in[i];
        while (atual != NULL) {
            LAdj novo = malloc(sizeof(struct aresta));
            novo -> dest = i;
            novo -> custo = atual -> custo;
            if (out[atual -> dest] == NULL) {
                novo -> prox = NULL;
            } else {
                novo -> prox = out[atual -> dest];
            }
            out[atual -> dest] = novo;
            atual = atual -> prox;
        }

    }
}

// 3.

int inDegree_v1(GrafoL g) {
    int mg = 0;
    for (int i = 0; i < NV; i++) {
        LAdj atual = g[i];
        int ga = 0;
        for (int j = 0; j < NV; j++) {
            LAdj temp = g[j];
            while (temp != NULL) {
                if (temp -> dest == i) {
                    ga++;
                }
                temp = temp -> prox;
            }
        }
        if (ga > mg) {
            mg = ga;
        }
    }

    return mg;
}

int inDegree_v2(GrafoL g) {
    GrafoL gi;
    inverte(g, gi);
    int mg = 0;
    for (int i = 0; i < NV; i++) {
        LAdj atual = gi[i];
        int ga = 0;
        while (atual != NULL) {
            ga++;
            atual = atual -> prox; 
        }
        if (ga > mg) {
            mg = ga;
        }
    }
    return mg;
}

// 4.

int colorOK (GrafoL g, int cor[]) {
    for (int i = 0; i < NV; i++) {
        LAdj atual = g[i];
        while (atual != NULL) {
            if (cor[i] == cor[atual -> dest]) {
                return 0;
            }
            atual = atual -> prox;
        }
    }
    return 1;
}

// 5.

int homomorfOK(GrafoL g, GrafoL h, int f[]) {
    for (int i = 0; i < NV; i++) {
        LAdj atualg = g[i];
        while (atualg != NULL) {
            int ga = i;
            int gb = atualg->dest;

            int ha = f[ga];
            int hb = f[gb];

            LAdj atualh = h[ha];
            int e = 0;

            while (atualh != NULL) {
                if (atualh -> dest == hb) {
                    e = 1;
                    break;
                }
                atualh = atualh->prox;
            }

            if (!e) {
                return e;
            }

            atualg = atualg->prox;
        }
    }
    return 1;
}

// Travessias...

int main() {
    GrafoM m = {
        {0, 5, 0, 2, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 8, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 2, 7, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0, 0, 0, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    GrafoL l;
    fromMat(m, l);
    imprimeListaAdj(l);

    return 0;
}
