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
    if (t -> left -> bf == LH) {
        t = rotateRight(t);
        t -> bf = EH;
        t -> right -> bf = EH; 
    } else {
        t -> left = rotateLeft(t -> left);
        t = rotateRight(t);
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

Tree insertTree(Tree t, TreeEntry e, int * cresceu) {
    if (t == NULL) {
        t = (Tree)malloc(sizeof(struct treenode));
        t -> entry = e;
        t -> right = t -> left = NULL;
        t -> bf = EH;
        * cresceu = 1;
    } else if (e > t -> entry) {
        t -> right = insertTree(t -> right, e, cresceu);
        if (* cresceu) {
            switch (t -> bf) {
                case LH:
                    t -> bf = EH;
                    * cresceu = 0;
                    break;
                case EH:
                    t -> bf = RH;
                    * cresceu = 1;
                    break;
                case RH:
                    t = balanceRight(t);
                    * cresceu = 0;
            }
        }
    } else {
        t -> left = insertTree(t -> left, e, cresceu);
        if (* cresceu) {
        switch (t -> bf) {
                case RH:
                    t -> bf = EH;
                    * cresceu = 0;
                    break;
                case EH:
                    t -> bf = LH;
                    * cresceu = 1;
                    break;
                case LH:
                    t = balanceLeft(t);
                    * cresceu = 0;
            }
        }
    }
    return t;
}

int nonAVL_treeHeight(Tree t) {
    int l, r;
    if (t == NULL) return 0;
    l = nonAVL_treeHeight(t -> left);
    r = nonAVL_treeHeight(t -> right);
    if (l > r) return l + 1;
    else return r + 1;
}

int AVL_treeHeight(Tree t) {
    int l, r;
    if (t == NULL) return 0;
    if (t -> bf == LH) {
        return 1 + AVL_treeHeight(t -> left);
    } else {
        return 1 + AVL_treeHeight(t -> right);
    }
}
    