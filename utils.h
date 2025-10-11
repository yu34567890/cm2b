#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "token.h"


size_t get_row(size_t index);
size_t get_column( size_t index);
unsigned int hextouint(const char* hex);
bool iskeyword(char* input);
char *token_to_string(Token_t token);

#endif // UTILS_H