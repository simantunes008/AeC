#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Size 100
#define Free 0
#define Used 1
#define Del 2

// Closed adressing hash table
typedef struct nodo {
    char * chave; 
    int ocorr;
    struct nodo * prox;
} Nodo, * THash1[Size];

// Open adressing hash table
typedef struct bucket {
    int status; // Free | Used | Del
    char * chave; 
    int ocorr;
} THash2[Size];

// Função hash
unsigned hash(char * str) {
    unsigned hash = 5381;
    int c;
    while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % Size; // Tive que divir pelo Size porque estava a gerar índices demasiado grandes
}

/*
** Chaining
** 1.
*/
void initEmpty1(THash1 t) {
    for (int i = 0; i < Size; i++) {
        t[i] = NULL;
    }
}

/*
** 2.
*/
void add1(char * s, THash1 t) {
    unsigned i = hash(s);
    Nodo * atual = t[i];
    while (atual) {
        if (strcmp(atual -> chave, s) == 0) {
            atual -> ocorr++;
            return;
        }
        atual = atual -> prox;
    }
    Nodo * nodo = malloc(sizeof(Nodo));
    nodo -> chave = strdup(s);
    nodo -> ocorr = 1;
    nodo -> prox = t[i];
    t[i] = nodo;
}

/*
** 3.
*/
int lookup1(char * s, THash1 t) {
    unsigned i = hash(s);
    Nodo * atual = t[i];
    while (atual) {
        if (strcmp(atual -> chave, s) == 0) {
            return atual -> ocorr;
        }
        atual = atual -> prox;
    }
    return 0;
}

/*
** 4.
*/
int remove1(char * s, THash1 t) {
    unsigned i = hash(s);
    Nodo * atual = t[i];
    Nodo * anterior = NULL;
    while (atual) {
        if (strcmp(atual -> chave, s) == 0) {
            if (anterior) {
                anterior -> prox = atual -> prox;
            } else {
                t[i] = atual -> prox;
            }
            free(atual -> chave);
            free(atual);
            return 0;
        }
        anterior = atual;
        atual = atual -> prox;
    }
    return 1;
}

/*
** Open Addressing
** 1.
*/
int where(char * s, THash2 t) {
    unsigned i = hash(s);
    while (t[i].status != Free && strcmp(t[i].chave, s) != 0) {
        i++;  
    }
    return i;
}

/*
** 2.
** a)
*/
void initEmpty2(THash2 t) {
    for (int i = 0; i < Size; i++) {
        t[i].status = Free;
        t[i].chave = NULL;
        t[i].ocorr = 0;
    }
}

// b)
void add2(char * s, THash2 t) {
    unsigned i = hash(s);
    while (t[i].status != Free && strcmp(t[i].chave, s) != 0) {
        i++;  
    }
    if (t[i].status != Used) {
        t[i].status = Used;
        t[i].chave = strdup(s);
        t[i].ocorr = 1;
    } else {
        t[i].ocorr++;
    }
}

// c)
int lookup2(char * s, THash2 t) {
    unsigned i = hash(s);
    while (t[i].status != Free && strcmp(t[i].chave, s) != 0) {
        i++;  
    }
    if (t[i].status == Used) {
        return t[i].ocorr;
    } else {
        return 0;
    }
}

// d)
int remove2(char * s, THash2 t) {
    unsigned i = hash(s);
    while (t[i].status != Free && strcmp(t[i].chave, s) != 0) {
        i++;
    }
    if (t[i].status == Used) {
        t[i].status = Del;
        t[i].chave = NULL;
        t[i].ocorr = 0;
        return 0;
    } else {
        return 1;
    }
}

/*
** 3.
*/
int garb_collection(THash2 t) {
    THash2 temp;
    initEmpty2(temp);

    int size = 0;

    for (int i = 0; i < Size; i++) {
        if (t[i].status == Used) {
            for (int j = 0; j < t[i].ocorr; j++) {
                add2(t[i].chave, temp);
            }
            size++;
        }
        if (t[i].status == Del) {
            size++;
        }
    }

    if (size == 0) {
        return 1;
    }

    initEmpty2(t);

    for (int i = 0; i < Size; i++) {
        if (temp[i].status == Used) {
            for (int j = 0; j < temp[i].ocorr; j++) {
                add2(temp[i].chave, t);
            }
            free(temp[i].chave);
        }
    }

    return 0;
}

/*
** 4. e 5.
** Fiquei com preguiça.
*/
