#include "utils.h"

size_t get_row(size_t index)
{
    size_t row = 1;
    for (size_t i = 0; i < index && code[i] != '\0'; i++) {
        if (code[i] == '\n') {
            row++;
        }
    }
    return row;
}

size_t get_column(size_t index)
{
    size_t column = 1;
    for (size_t i = index; i > 0 && code[i - 1] != '\n'; i--) {
        column++;
    }
    return column;
}

char *token_to_string(Token_t token) {
    switch (token.type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_KEYWORD: return "KEYWORD";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_STAR: return "STAR";
        case TOKEN_SLASH: return "SLASH";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_EQ: return "EQ";
        case TOKEN_NEQ: return "NEQ";
        case TOKEN_LT: return "LT";
        case TOKEN_LTE: return "LTE";
        case TOKEN_GT: return "GT";
        case TOKEN_GTE: return "GTE";
        case TOKEN_OPENING_PAREN: return "TOKEN_OPENING_PAREN";
        case TOKEN_CLOSING_PAREN: return "TOKEN_CLOSING_PAREN";
        default: return "UNKNOWN";
    }
}
/*

void gen_keyword_hash() { // to generate switch case fast for the iskeyword
    char *keywords[] = {
        "if",
        "then",
        "else",
        "set",
        "init",
        "asm",
        "label",
        "goto",
        "gosub",
        "scope"
    };

    size_t count = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < count; i++) {
        printf("case %u:\n      if(strcmp(\"%s\",input) == 0) return true;\n        break;\n",hash(keywords[i]),keywords[i]);
    }

}
*/

bool iskeyword(char* input) { // todo optimize it with hash strings


    switch(hash(input)) // todo fix collisions
    {
    case 565107:
        if(strcmp("if",input) == 0) return true;
            break;
    case 3485174323:
        if(strcmp("then",input) == 0) return true;
            break;
    case 2947459201:
        if(strcmp("else",input) == 0) return true;
            break;
    case 3330387112:
        if(strcmp("set",input) == 0) return true;
            break;
    case 3465943172:
        if(strcmp("init",input) == 0) return true;
            break;
    case 2809269541:
        if(strcmp("asm",input) == 0) return true;
            break;
    case 1196254976:
        if(strcmp("label",input) == 0) return true;
            break;
    case 1117160149:
        if(strcmp("goto",input) == 0) return true;
            break;
    case 2750591888:
        if(strcmp("gosub",input) == 0) return true;
            break;
    case 3301431951:
        if(strcmp("ret",input) == 0) return true;
            break;
    case 2573301126:
        if(strcmp("scope",input) == 0) return true;
            break;
    }
    return false;
}
const char* nodetype_to_string(Nodetype type) {
    switch (type) {
        case PROGRAM: return "PROGRAM";
        case BINARY_EXPR: return "BINARY_EXPR";
        case LITERAL: return "LITERAL";
        case IDENTIFIER: return "IDENTIFIER";
        case LABEL: return "LABEL";
        case ASSIGN: return "ASSIGN";
        case DECLARE: return "DECLARE";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case GOTO: return "GOTO";
        case GOSUB: return "GOSUB";
        case RET: return "RET";
        case ASM: return "ASM";
        default: return "UNKNOWN";
    }
}

static inline char getprecedence(Token_t c)
{
    switch (c.type)
    {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        return 1;
        case TOKEN_STAR:
        case TOKEN_SLASH:
        return 2;
    }
    return 0;
}


Token_t* topostfix(Token_t* infix)
{
    int i=0;
    int opcodes=0;
    for(;infix[i].type != TOKEN_EOF;i++)
    {
        if(getprecedence(infix[i]))
        {
            opcodes++;
        }
        else if (infix[i].type == TOKEN_OPENING_PAREN || infix[i].type == TOKEN_CLOSING_PAREN)
        {
            opcodes++;
        }
        
    }
    int stack_ptr = 0;
    int result_ptr = 0;

    
    Token_t* stack = calloc(opcodes + 1, sizeof(Token_t));
    
    Token_t* result = calloc(i + 1, sizeof(Token_t));

    result[i].type=TOKEN_EOF;
    result[i].value=strdup("EOF");
    result[i].index=infix[i-1].index;
    
    
    for(i=0; infix[i].type != TOKEN_EOF; i++)
    {

        if (infix[i].type == TOKEN_NUMBER)
        {
            result[result_ptr++] = infix[i];
        }
        else if(getprecedence(infix[i]))
        {
            
            while(stack_ptr && (getprecedence(stack[stack_ptr]) > getprecedence(infix[i]) && infix[i].type != TOKEN_OPENING_PAREN && infix[i].type != TOKEN_CLOSING_PAREN))
            {
                
                result[result_ptr++] = stack[stack_ptr--];
            }
           
            stack[++stack_ptr] = infix[i];
        }
        else if(infix[i].type == TOKEN_OPENING_PAREN)
        {
            stack[++stack_ptr] = infix[i];
            
        }
        else if(infix[i].type == TOKEN_CLOSING_PAREN)
        {
            while(stack_ptr && stack[stack_ptr].type != TOKEN_OPENING_PAREN)
            {
                
                result[result_ptr++] = stack[stack_ptr--];
            }
            if(stack_ptr!=0)
            {
                stack[stack_ptr--];
            }
            else
            {
                printf("POSTFIX ERROR: PAREN NOT CLOSED at row %zu column %zu\n",get_row(infix[0].index),get_column(infix[0].index));
                exit(1);
            }
        }
    }
    for(;stack_ptr>=0;)
    {
        
        result[result_ptr++] = stack[stack_ptr--];
    }
    free(stack);

    
    return result;
}


exptree_t*  to_exptree(Token_t* expression)
{

    int i = 0;
    for(i=0; expression[i].type; i++);
    exptree_t** stack = calloc(i,sizeof(exptree_t*));
    int stack_ptr = -1;

    for(i=0; expression[i].type; i++)
    {
        if(expression[i].type == TOKEN_NUMBER)
        {
            exptree_t* p = malloc(sizeof(exptree_t));
            p->type = LITERAL;
            p->value = (void *)expression[i].value;
            p->left = NULL;
            p->right = NULL;
            stack[++stack_ptr] = p;
        }
        else if(expression[i].type >= TOKEN_PLUS && expression[i].type <= TOKEN_GTE) // optimizasion hack !!!
        {
            exptree_t* p = malloc(sizeof(exptree_t));
            p->type = OP;
            p->value = (void *)expression[i].value;
            p->right = stack[stack_ptr--];
            p->left = stack[stack_ptr--];
            stack[++stack_ptr] = p;
        }
    }
    exptree_t* result = stack[0];
    free(stack);
    return result; // should be finish
}


void print_exptree(exptree_t* node) 
{

    if (!node) return;

    if (node->type == LITERAL) {
        printf("%s", (char*)node->value);
    } else if (node->type == OP) {
        printf("(");
        print_exptree(node->left);  
        printf(" %s ", (char*)node->value);
        print_exptree(node->right);  
        printf(")");
    }
}

void print_tree(Node_t* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) 
    {
        printf("  ");
    }

    printf("%s", nodetype_to_string(node->nodetype));
    if (node->nodetype == ASSIGN)
    {
        printf("\n");
        for (int i = 0; i < depth+1; i++) 
        {
            printf("  ");
        }
        printf("EXPRESSION:");
        print_exptree((exptree_t*)node->data);

    }
    else if (node->data) 
    {
        printf(": %s", (char*)node->data); 
    }

    printf("\n");

    for (unsigned int i = 0; i < node->child_count; i++) 
    {
        print_tree(node->child[i], depth + 1);
    }
}
