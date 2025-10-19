#ifndef NODE_H
#define NODE_H
typedef enum 
{
    EMPTY, // empty node for calloc calls
    PROGRAM, // ROOT node

    BINARY_EXPR, // binary expression + - * /
    LITERAL,
    IDENTIFIER, // variable acces

    SCOPE, // scope definition
    LABEL, // label definition
    ASSIGN, // variable assign eg a = 2;
    DECLARE, // variable declaration eg set a=2;
    IF,
    ELSE,     // if <else statement
    GOTO,
    GOSUB,
    RET,
    SCOPE_ACCES, //scope accesing eg math.varname;
    ASM // asm code eg asm "MOV R1,R2";

} Nodetype;

typedef struct Node_t 
{
    Nodetype nodetype;
    void* data; // node data pointer

    struct Node_t** child;
    unsigned int child_count;
} Node_t;
#endif // NODE_H