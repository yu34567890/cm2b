#ifndef EXPTREE_H
#define EXPTREE_H

typedef enum
{
    LITERAL,
    OP
} exptype;

typedef struct expression_tree
{
    exptype type;
    struct expression_tree* left;
    void* value;
    struct expression_tree* right;
}exptree_t;

#endif