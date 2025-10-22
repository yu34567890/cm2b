#ifndef NODE_H
#define NODE_H
typedef enum 
{
    EMPTY, // empty node for calloc calls
    PROGRAM, // ROOT node

    BINARY_EXPR, // binary expression + - * /
    IDENTIFIER, // variable acces

    LABEL, // label definition
    ASSIGN, // variable assign eg a = 2;
    DECLARE, // variable declaration eg set a=2;
    IF,
    ELSE,     // if <else statement
    GOTO,
    GOSUB,
    RET,
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