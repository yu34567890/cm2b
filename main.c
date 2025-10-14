#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "globals.h"

char* code; 

#include "utils.h"
#include "lexer.h"
#include "parser.h"


const char* nodetype_to_string(Nodetype type) {
    switch (type) {
        case PROGRAM: return "PROGRAM";
        case BINARY_EXPR: return "BINARY_EXPR";
        case LITERAL: return "LITERAL";
        case IDENTIFIER: return "IDENTIFIER";
        case SCOPE: return "SCOPE";
        case LABEL: return "LABEL";
        case ASSIGN: return "ASSIGN";
        case DECLARE: return "DECLARE";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case SCOPE_ACCES: return "SCOPE_ACCES";
        default: return "UNKNOWN";
    }
}

void print_tree(Node_t* node, int depth) {
    if (!node) return;

    // Indent based on depth
    for (int i = 0; i < depth; i++) {
        printf("  "); // 2 spaces per level
    }

    // Print node type
    printf("%s", nodetype_to_string(node->nodetype));

    // Optionally print node data if it's a string
    if (node->data) {
        printf(": %s", (char*)node->data); // assuming data is string, adjust as needed
    }

    printf("\n");

    // Recursively print children
    for (unsigned int i = 0; i < node->child_count; i++) {
        print_tree(node->child[i], depth + 1);
    }
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("ERROR wrong number of arguments. Usage: %s FILE\n", argv[0]);
        return 1;
    }

    FILE* fptr = fopen(argv[1], "r");
    if (!fptr) {
        printf("ERROR The file could not be opened.\n");
        return 1;
    }

    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);

    code = malloc(size + 1);  
    if (!code)
    {
        fclose(fptr);
        return 1;
    }

    fread(code, 1, size, fptr);
    code[size] = '\0';
    fclose(fptr);

    Token_t* tokens = tokenize(code);

    for (size_t index = 0; tokens[index].type; index++)
    {
        printf("row %zu column %zu token %s value %s\n",
               get_row(tokens[index].index),
               get_column(tokens[index].index),
               token_to_string(tokens[index]),
               tokens[index].value);
    }
    Node_t* tree = parse(tokens);
    print_tree(tree,1);
    printf("babalar\n");

    free(code);  
    return 0;
}
