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

// 1 Representações

// 1.

void fromMat(GrafoM in, GrafoL out) {
    for (int i = 0; i < NV; i++) {
        out[i] = NULL;
        for (int j = NV - 1; j >= 0; j--) {
            if (in[i][j] != 0) {
                LAdj novo = malloc(sizeof(struct aresta));
                novo -> dest = j;
                novo -> custo = in[i][j];
                novo -> prox = out[i];
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
            novo -> prox = out[atual -> dest];
            out[atual -> dest] = novo;
            atual = atual -> prox;
        }

    }
}

// 3.

int inDegree_v1(GrafoL g) {
    int maxInDegree = 0;
    for (int i = 0; i < NV; i++) {
        int inDegree = 0;
        for (int j = 0; j < NV; j++) {
            LAdj atual = g[j];
            while (atual != NULL) {
                if (atual -> dest == i) {
                    inDegree++;
                }
                atual = atual -> prox;
            }
        }
        if (inDegree > maxInDegree) {
            maxInDegree = inDegree;
        }
    }
    return maxInDegree;
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

int colorOK(GrafoL g, int cor[]) {
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
            int gb = atualg -> dest;

            int ha = f[ga];
            int hb = f[gb];

            LAdj atualh = h[ha];
            int e = 0;

            while (atualh != NULL) {
                if (atualh -> dest == hb) {
                    e = 1;
                    break;
                }
                atualh = atualh -> prox;
            }

            if (!e) {
                return 0;
            }
            
            atualg = atualg -> prox;
        }
    }
    return 1;
}

// 2 Travessias

int DFRec(GrafoL g, int or, int v[], int p[], int l[]) {
    int i;
    LAdj a;
    i = 1;
    v[or] = -1;
    for (a = g[or]; a != NULL; a = a->prox)
        if (!v[a->dest]) {
            p[a->dest] = or;
            l[a->dest] = 1 + l[or];
            i += DFRec(g, a->dest, v, p, l);
        }
    v[or] = 1;
    return i;
}

int DF(GrafoL g, int or, int v[], int p[], int l[]) {
    int i;
    for (i = 0; i < NV; i++) {
        v[i] = 0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1;
    l[or] = 0;
    return DFRec(g, or, v, p, l);
}

int BF(GrafoL g, int or, int v[], int p[], int l[]) {
    int i, x;
    LAdj a;
    int q[NV], front, end;
    
    for (i = 0; i < NV; i++) {
        v[i] = 0;
        p[i] = -1;
        l[i] = -1;
    }

    front = end = 0;
    q[end++] = or; // enqueue
    v[or] = 1;
    l[or] = 0;
    p[or] = -1; // redundante
    i = 1;

    while (front != end) {
        x = q[front++]; // dequeue

        for (a = g[x]; a != NULL; a = a->prox) {
            if (!v[a -> dest]) {
                i++;
                v[a -> dest] = 1;
                p[a -> dest] = x;
                l[a -> dest] = 1 + l[x];
                q[end++] = a -> dest; // enqueue
            }
        }
    }

    return i;
}

// 1.

int maisLonga(GrafoL g, int or, int p[]) {
    int max, x;
    LAdj atual;
    int v[NV], f[NV], l[NV], q[NV], front, end;

    for (int i = 0; i < NV; i++) {
        v[i] = 0;
        f[i] = -1;
        l[i] = -1;
    }

    front = end = max = 0;
    q[end++] = or;
    v[or] = 1;
    l[or] = 0;
    f[or] = -1;
    p[0] = or;

    while (front != end) {
        x = q[front++];

        for (atual = g[x]; atual != NULL; atual = atual -> prox) {
            if (!v[atual -> dest]) {
                q[end++] = atual->dest;
                v[atual -> dest] = 1;
                l[atual -> dest] = 1 + l[x];
                f[atual -> dest] = x;

                if (l[atual -> dest] > max) {
                    max = l[atual -> dest];
                    int maisLonge = atual -> dest, temp = max;
                    while (f[maisLonge] != -1) {
                        p[temp--] = maisLonge;
                        maisLonge = f[maisLonge];
                    }
                }
            }
        }
    }

    return max;
}

// 2.

int componentes(GrafoL g, int c[]) {
    return 0;
}

int main() {
    GrafoM grafoM = {
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

    GrafoL grafoL;
    fromMat(grafoM, grafoL);

    return 0;
}
