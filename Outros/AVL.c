#include <stdio.h>
#include <stdlib.h>

#include <AVL.h>

typedef int TreeEntry;

typedef enum balancefactor {LH, EH, RH} BalanceFactor;

struct treenode {
    BalanceFactor bf;
    TreeEntry entry;
    struct treenode * left;
    struct treenode * right;
};

typedef struct treenode * Tree;

// requires: (t != NULL) && ((t -> right != NULL) || (t -> left != NULL))

Tree rotateLeft(Tree t) {
    Tree aux = t -> right;
    t -> right = aux -> left;
    aux -> left = t;
    t = aux;
    return t;
}

Tree rotateRight(Tree t) {
    Tree aux = t -> left;
    t -> left = aux -> right;
    aux -> right = t;
    t = aux;
    return t;
}

Tree balanceRight(Tree t) {
    if (t -> right -> bf == RH) {
        t = rotateLeft(t);
        t -> bf = EH;
        t -> left -> bf = EH;
    } else {
        t -> right = rotateRight(t -> right);
        t = rotateLeft(t);
        switch (t -> bf) {
            case EH:
                t -> left -> bf = EH;
                t -> right -> bf = EH;
                break;
            case LH:
                t -> left -> bf = EH;
                t -> right -> bf = RH;
                break;
            case RH:
                t -> left -> bf = LH;
                t -> right -> bf = EH;
        }
        t -> bf = EH;
    }
    return t;
}

Tree balanceLeft(Tree t) {

}
