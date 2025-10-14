#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "globals.h"

char* code; 

#include "utils.h"
#include "lexer.h"
#include "parser.h"






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
    /*
    for (size_t index = 0; tokens[index].type; index++)
    {
        printf("row %zu column %zu token %s value %s\n",
               get_row(tokens[index].index),
               get_column(tokens[index].index),
               token_to_string(tokens[index]),
               tokens[index].value);
    }*/
    Node_t* tree = parse(tokens);
    print_tree(tree,2);
    printf("babalar\n");

    free(code);  
    return 0;
}
