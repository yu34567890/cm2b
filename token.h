#ifndef TOKEN_H
#define TOKEN_H
#include <stddef.h>
typedef enum 
{
    TOKEN_EOF,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_LTE,
    TOKEN_GT,
    TOKEN_GTE,
    TOKEN_UNKNOW
} Tokentype;

typedef struct 
{
    Tokentype type;
    char* value;   
    size_t index; // Position in the input string can be used to get row and column 
} Token_t;



#endif // TOKEN_H