#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#include "token.h"
#include "utils.h"

Token_t* tokenize(char* input);




#endif // LEXER_H