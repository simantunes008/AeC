#ifndef GRAPH_H
#define GRAPH_H

/**
 * @struct aresta
 * @brief Estrutura para representar um grafo através de listas de adjacências.
 */
typedef struct aresta * LAdj, * GrafoL[];

/**
 * @typedef GrafoM
 * @brief Estrutura para representar um grafo através de uma matriz de ajdacências.
 */
typedef int GrafoM;

void fromMat(GrafoM in, GrafoL out);

void inverte(GrafoL in, GrafoL out);

int inDegree_v1(GrafoL g);

int inDegree_v2(GrafoL g);

int colorOK(GrafoL g, int cor[]);

int homomorfOK(GrafoL g, GrafoL h, int f[]);

#endif
