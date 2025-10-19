#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h> 
#include <stdarg.h>
#include <stdio.h>
#include "token.h"
#include "hashmap.h"
#include "utils.h"
#include "node.h"




Node_t* parse(Token_t* tokens);

#endif //PARSER_H