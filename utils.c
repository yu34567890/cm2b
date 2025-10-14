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
        case SCOPE: return "SCOPE";
        case LABEL: return "LABEL";
        case ASSIGN: return "ASSIGN";
        case DECLARE: return "DECLARE";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case SCOPE_ACCES: return "SCOPE_ACCES";
        case ASM: return "ASM";
        default: return "UNKNOWN";
    }
}
void print_tree(Node_t* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("%s", nodetype_to_string(node->nodetype));

    if (node->data) {
        printf(": %s", (char*)node->data); 
    }

    printf("\n");

    for (unsigned int i = 0; i < node->child_count; i++) {
        print_tree(node->child[i], depth + 1);
    }
}