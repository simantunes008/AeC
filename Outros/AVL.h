#ifndef AVL_H
#define AVL_H

/**
 * @struct treenode
 * @brief Estrutura para representar uma árvore AVL.
 */
typedef struct treenode * Tree;

/**
 * @brief Realiza uma rotação simples à esquerda da árvore com raíz apontada por t.
 *
 * @param t
 * @return O endereço da nova raiz.
 */
Tree rotateLeft(Tree t);

/**
 * @brief Realiza uma rotação simples à direita da árvore com raíz apontada por t.
 *
 * @param t
 * @return O endereço da nova raiz.
 */
Tree rotateRight(Tree t);

/**
 * @brief Função que corrige a estrutura de uma árvore que está desequilibrada para a direita.
 *
 * @param t
 * @return O endereço da nova raiz.
 */
Tree balanceRight(Tree t);

/**
 * @brief Função que corrige a estrutura de uma árvore que está desequilibrada para a esquerda.
 *
 * @param t
 * @return O endereço da nova raiz.
 */
Tree balanceLeft(Tree t);

/**
 * @brief Insere um novo elemento numa árvore AVL
 *
 * @param t
 * @return O endereço da nova raiz.
 */
Tree insertTree(Tree t, TreeEntry e, int * cresceu);

/**
 * @brief Calcula a altura de uma árvore binária em tempo Θ(N).
 *
 * @param t
 * @return A altura da árvore.
 */
int nonAVL_treeHeight(Tree t);

/**
 * @brief Calcula a altura de uma árvore AVL em tempo Θ(log N).
 *
 * @param t
 * @return A altura da árvore.
 */
int AVL_treeHeight(Tree t);

#endif
