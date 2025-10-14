#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h> 
#include <stdarg.h>
#include <stdio.h>
#include "token.h"
#include "hashmap.h"
#include "utils.h"


typedef enum 
{
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
    SCOPE_ACCES, //scope accesing eg math.varname;
} Nodetype;

typedef struct Node_t 
{
    Nodetype nodetype;
    void* data; // node data pointer

    struct Node_t** child;
    unsigned int child_count;
} Node_t;


Node_t* parse(Token_t* tokens);

#endif //PARSER_H