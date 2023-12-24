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

#endif
