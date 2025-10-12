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


bool iskeyword(char* input) { // thank you chatgpt for this garbage 
    const char *keywords[] = {
        "if",
        "then",
        "endif",
        "set",
        "init",
        "asm",
        "label",
        "goto",
        "gosub"
    };

    size_t count = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < count; i++) {
        if (strcmp(input, keywords[i]) == 0)
            return true;
    }

    return false;
}