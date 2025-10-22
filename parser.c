#include "parser.h"
#include "utils.h"


Node_t ROOT_NODE;
/*
example usage
    bucket_t testhashmap = init_hashmap(2048);
    push_int(&testhashmap,"testkey",2096);
    printf("%u",*(get_key(&testhashmap,"testkey")));
*/

/*
node type so i dont keep checking parser.h file
typedef struct Node_t 
{
    Nodetype nodetype;
    void* data; // node data pointer

    struct Node_t** child;
    unsigned int child_count;
} Node_t;
*/

void print_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    printf("\033[1;31m");       // start red color
    vprintf(fmt, args);         // formatted print
    printf("\033[0m\n");        // reset color + newline

    va_end(args);
}



void insert_node(Node_t *target_node,Node_t *node)
{
    if(target_node->child_count == 0)
    {
        target_node->child_count++;
        target_node->child = malloc(1*sizeof(Node_t*));
        target_node->child[0] = node;
        return;       
    }
    target_node->child_count++;
    target_node->child = realloc(target_node->child,target_node->child_count*sizeof(Node_t*));
    target_node->child[target_node->child_count-1] = node;
}

Node_t* create_node(Nodetype nodetype, void* data) {
    Node_t* node = calloc(1, sizeof(Node_t));
    if (!node) return NULL; // allocation failed

    node->nodetype = nodetype;
    node->data = data;        // just store pointer (no copy)
    node->child = NULL;       // no children yet
    node->child_count = 0;

    return node;
}

Node_t* parse_line(Token_t* tokens) // todo optimize it with switch and use hash like in utils.c iskeyword func
{
    Node_t* result;
    if(tokens[0].type==TOKEN_KEYWORD)
    {
        if(strcmp(tokens[0].value,"label") == 0 ) 
        {
            
            if(tokens[1].type == TOKEN_EOF)
            {
                print_error("ERROR: unexpected eof at row %zu column %zu did you forget semicollon ?",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            if(tokens[1].type != TOKEN_IDENTIFIER)
            {
                print_error("ERROR: label expected identifier at row %zu column %zu got %s instead ?",get_row(tokens[1].index),get_column(tokens[1].index),tokens[1].type);
                exit(1); 
            }
            result = malloc(sizeof(Node_t));
            result->nodetype = LABEL;
            result->data = strdup(tokens[1].value);
            result->child = NULL;
            result->child_count = 0;

            return result;
        }
        else if(strcmp(tokens[0].value,"asm") == 0 ) 
        {
            
            if(tokens[1].type == TOKEN_EOF)
            {
                print_error("ERROR: unexpected eof at row %zu column %zu did you forget semicollon ?",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            if(tokens[1].type != TOKEN_STRING)
            {
                print_error("ERROR: asm expected string at row %zu column %zu got %s instead ?",get_row(tokens[1].index),get_column(tokens[1].index),tokens[1].type);
                exit(1); 
            }
            result = malloc(sizeof(Node_t));
            result->nodetype = ASM;
            result->data = strdup(tokens[1].value);
            result->child = NULL;
            result->child_count = 0;

            return result;
        }
        else if(strcmp(tokens[0].value,"goto") == 0)
        {
            if(tokens[1].type == TOKEN_EOF)
            {
                print_error("ERROR: unexpected eof at row %zu column %zu did you forget semicollon ?",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            if(tokens[1].type != TOKEN_IDENTIFIER)
            {
                print_error("ERROR: goto expected identifier at row %zu column %zu got %s instead ?",get_row(tokens[1].index),get_column(tokens[1].index),tokens[1].type);
                exit(1); 
            }
            result = malloc(sizeof(Node_t));
            result->nodetype = GOTO;
            result->data = strdup(tokens[1].value);
            result->child = NULL;
            result->child_count = 0;
            return result;
        }
        else if(strcmp(tokens[0].value,"gosub") == 0)
        {
            if(tokens[1].type == TOKEN_EOF)
            {
                print_error("ERROR: unexpected eof at row %zu column %zu did you forget semicollon ?",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            if(tokens[1].type != TOKEN_IDENTIFIER)
            {
                print_error("ERROR: goto expected identifier at row %zu column %zu got %s instead ?",get_row(tokens[1].index),get_column(tokens[1].index),tokens[1].type);
                exit(1); 
            }
            result = malloc(sizeof(Node_t));
            result->nodetype = GOSUB;
            result->data = strdup(tokens[1].value);
            result->child = NULL;
            result->child_count = 0;
            return result;
        }
        else if(strcmp(tokens[0].value,"ret") == 0)
        {
            if(tokens[1].type != TOKEN_EOF)
            {
                print_error("ERROR: unexpected token at row %zu column %zu did you forget semicollon ?",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            
            result = malloc(sizeof(Node_t));
            result->nodetype = RET;
            result->data = strdup("\0");
            result->child = NULL;
            result->child_count = 0;
            return result;
        }
        if(strcmp(tokens[0].value,"set") == 0 ) 
        {
            if(tokens[2].type != TOKEN_ASSIGN)
            {
                print_error("ERROR: expected TOKEN_ASSIGN at row %zu column %zu",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }

            if(tokens[1].type != TOKEN_IDENTIFIER)
            {
                print_error("ERROR: expected TOKEN_IDENTIFIER at row %zu column %zu",get_row(tokens[1].index),get_column(tokens[1].index));
                exit(1); 
            }
            
            Token_t* postfix = topostfix(tokens + 3);

            
            
            result = calloc(1,sizeof(Node_t));
            Node_t* current = result;
            Node_t* result_node;
            result->nodetype = ASSIGN;
            result->data =(void*)tokens[1].value;
            result->child_count = 0;

            for(int i = 0; postfix[i].type;i++)
            {
                if(postfix[i].type == TOKEN_NUMBER)
                {
                    
                }
                else
                {

                }
            }

            free(postfix);
            return result;
        }
    }
}


Node_t* parse(Token_t* tokens)
{

    Node_t* ROOT_NODE = malloc(sizeof(Node_t));
    ROOT_NODE->nodetype = PROGRAM;
    ROOT_NODE->child_count = 0;
    ROOT_NODE->child = NULL;
    ROOT_NODE->data = NULL;
    Token_t* args;
    size_t i2=0;
    size_t i=0;
    for(; tokens[i].type != TOKEN_EOF; i++)
    {
        Token_t current = tokens[i];
        switch(current.type)
        {
            case TOKEN_KEYWORD: 
                for(i2=i;tokens[i2].type != TOKEN_SEMICOLON; i2++)
                {
                     if(tokens[i2].type == TOKEN_EOF)
                     {
                        print_error("ERROR: unexpected eof at row %zu column %zu did you forget semicollon ?",get_row(tokens[i].index),get_column(tokens[i].index));
                        exit(1);
                     }
                }
                size_t len = i2 - i;
                args = malloc((len+1)*sizeof(struct Token_t));
                args[len] = (Token_t){TOKEN_EOF,NULL,0}; 
                memcpy(args, tokens+i, len*sizeof(struct Token_t));
                insert_node(ROOT_NODE,parse_line(args));
                free(args);
                i=i2;
                break;
        }
    }
    return ROOT_NODE;
}