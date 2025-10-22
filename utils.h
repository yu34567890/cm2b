#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "node.h"
#include "token.h"
#include "globals.h"
#include "hashmap.h" // for hash() function
#include "exptree.h"


size_t get_row(size_t index);
size_t get_column( size_t index);
unsigned int hextouint(const char* hex);
bool iskeyword(char* input);
char *token_to_string(Token_t token);
const char* nodetype_to_string(Nodetype type);
void print_tree(Node_t* node, int depth);
Token_t* topostfix(Token_t* infix);
exptree_t*  to_exptree(Token_t* expression);
void print_exptree(exptree_t* node);
#endif // UTILS_H