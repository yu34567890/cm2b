#include "utils.h"
#include "hashmap.h" // for hash() function


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
if: 565107
then: 3485174323
else: 2947459201
set: 3330387112
init: 3465943172
asm: 2809269541
label: 1196254976
goto: 1117160149
gosub: 2750591888
scope: 2573301126
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
        printf("case %u:\n",hash(keywords[i]));
    }

}
*/

bool iskeyword(char* input) { // todo optimize it with hash strings


    switch(hash(input)) // todo fix collisions
    {
        case 565107:
        case 3485174323:
        case 2947459201:
        case 3330387112:
        case 3465943172:
        case 2809269541:
        case 1196254976:
        case 1117160149:
        case 2750591888:
        case 2573301126:
            return true;
        default:
            return false;

    }
}