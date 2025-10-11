#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "utils.h"
#include "lexer.h"

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("ERROR wrong number of argument usage %s FILE",argv[0]);
        return 1;
    }
    FILE* fptr;
    fptr = fopen(argv[1],"r");

    if (fptr == NULL) {
        printf("ERROR The file is not opened.");
        return 1;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);
    char* buffer = malloc(size+1);
    if (!buffer)
    {
        fclose(fptr);
        return 1;
    }
    fread(buffer,1,size,fptr);
    buffer[size] = '\0';
    fclose(fptr);
    
    
    Token_t* tokens = tokenize(buffer);
    for(size_t index=0; tokens[index].type; index++)
    {
        printf("row %zu column %zu token %s value %s\n",get_row(buffer,tokens[index].index),get_column(buffer,tokens[index].index) ,token_to_string(tokens[index]), tokens[index].value);
    }
}