#ifndef HASHTABLE_H
#define HASHTABLE_H

/**
 * @struct nodo
 * @brief Estrutura para representar um nodo de uma Closed Adressing Hash Table.
 */
typedef struct nodo Nodo, * THashC[];

/**
 * @struct bucket
 * @brief Estrutura para representar um nodo de uma Open Adressing Hash Table.
 */
typedef struct bucket THashOA;

/**
 * @brief Inicializa um multi-conjunto a vazio.
 *
 * @param t
 * @return void.
 */
void initEmptyC(THashC t);

/**
 * @brief Regista mais uma ocorrência de um elemento a um multi-conjunto.
 *
 * @param s
 * @param t
 * @return void.
 */
void addC(char * s, THashC t);

/**
 * @brief Calcula a multiplicidade de um elemento num multi-conjunto.
 *
 * @param s
 * @param t
 * @return O número de vezes que o elemente ocorre.
 */
int lookupC(char * s, THashC t);

/**
 * @brief Remove uma ocorrência de um elemento de um multi-conjunto.
 *
 * @param s
 * @param t
 * @return 0 se for possível remover e 1 em caso contrário.
 */
int removeC(char * s, THashC t);

/**
 * @brief Calcula o índice de t onde s está (ou devia estar) armazenada.
 *
 * @param s
 * @param t
 * @return O índice calculado
 */
int where(char * s, THashOA t);

/**
 * @brief Inicializa um multi-conjunto a vazio.
 *
 * @param t
 * @return void.
 */
void initEmptyOA(THashOA t);

/**
 * @brief Regista mais uma ocorrência de um elemento a um multi-conjunto.
 *
 * @param s
 * @param t
 * @return void.
 */
void addOA(char * s, THashOA t);

/**
 * @brief Calcula a multiplicidade de um elemento num multi-conjunto.
 *
 * @param s
 * @param t
 * @return O número de vezes que o elemente ocorre.
 */
int lookupOA(char * s, THashOA t);

/**
 * @brief Remove uma ocorrência de um elemento de um multi-conjunto.
 *
 * @param s
 * @param t
 * @return 0 se for possível remover e 1 em caso contrário.
 */
int removeOA(char * s, THashOA t);

/**
 * @brief Reconstrói a tabela t de forma a não haver chaves apagadas (status == Del).
 *
 * @param s
 * @param t
 * @return 1 se a tabela t estiver vazia (status == Free) e 0 em caso contrário.
 */
int garb_collection(THashOA t);

#endif
