#include "parser.h"


/*
typedef struct Node_t 
{
    Nodetype nodetype;
    void* data; // node data pointer

    struct Node_t** child;
    unsigned int child_count;
} Node_t;
*/



/* todo finish this shit 
Node_t parse(Token_t* tokens)
{
    Node_t ROOT_NODE = {PROGRAM,NULL,NULL,0}; 
    Token_t* args;
    size_t i2=0;
    for(size_t i=0; tokens[i].type != TOKEN_EOF; i++)
    {
        Token_t current = tokens[i].type;
        switch(current.type)
        {
            case KEYWORD: 
                for(; tokens[i2].type != TOKEN_EOF && TOKEN_SEMICOLON; i2++);
                
                break;
        }
    }


}*/