#include "lexer.h"



Token_t* tokenize(char* input) { // todo add comments eg //
    Token_t* result = malloc((strlen(input)+1) * sizeof(Token_t)); // number of tokens must be smaller than the ammount of charachters 
    size_t token_pos = 0;
    size_t index = 0;
    for(; input[index]; index++)
    {
        
        if(isdigit((unsigned char)input[index]))
        {
            size_t index2=index;
            for(; isdigit((unsigned char)input[index2]); index2++);
            size_t len = index2 - index;
            char* matched = malloc(len+1);
            memcpy(matched, input + index, len);
            matched[len] = 0;
            
            result[token_pos].type = TOKEN_NUMBER;
            result[token_pos].index = index;
            result[token_pos++].value = matched;
            
            index = index2-1;
            continue;
        }
        else if(isalpha((unsigned char)input[index]))
        {
            size_t index2=index;
            for(; isalnum((unsigned char)input[index2]) || input[index2] == '.'; index2++);
            size_t len = index2 - index;
            char* matched = malloc(len+1);
            memcpy(matched, input + index, len);
            matched[len] = 0;
            if(iskeyword(matched))
            {
                result[token_pos].type = TOKEN_KEYWORD;
                result[token_pos].index = index;
                result[token_pos++].value = matched;
            }
            else
            {
                result[token_pos].type = TOKEN_IDENTIFIER;
                result[token_pos].index = index;
                result[token_pos++].value = matched;
            }
            index = index2-1;
            continue;
        }

        else if(input[index] == '"') 
        {
            index++;
            size_t index2=index;
            for(; input[index2] != '"'; index2++)
            {
                if(input[index2] == 0)
                {
                    printf("LEXER ERROR: unterminated string at row %zu column %zu\n", get_row(index),get_column(index));
                    fflush(stdout);
                    exit(1);

                }
            }
            size_t len = index2 - index;
            char* matched = malloc(len+1);
            memcpy(matched, input + index, len);
            matched[len] = 0;
            result[token_pos].type = TOKEN_STRING;
            result[token_pos].index = index;
            result[token_pos++].value = matched;
            index = index2;
        }
        else if(input[index] == '=')
        {
            if(input[index+1] == '=')
            {
                result[token_pos].type = TOKEN_EQ;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("==");
                index+=1;
            }
            else if(input[index+1] == '>')
            {
                result[token_pos].type = TOKEN_GTE;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("=>");
                index+=1;
            }
            else if(input[index+1] == '<')
            {
                result[token_pos].type = TOKEN_LTE;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("=<");
                index+=1;
            }
            else
            {
                result[token_pos].type = TOKEN_ASSIGN;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("=");
            }
        }
        else if(input[index] == '<')
        {
                result[token_pos].type = TOKEN_LT;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("<");
        }
        else if(input[index] == '>')
        {
                result[token_pos].type = TOKEN_GT;
                result[token_pos].index = index;
                result[token_pos++].value = strdup(">");
        }
        else if(input[index] == ';')
        {
                result[token_pos].type = TOKEN_SEMICOLON;
                result[token_pos].index = index;
                result[token_pos++].value = strdup(";");
        }

        else if(input[index] == '+')
        {
            result[token_pos].type = TOKEN_PLUS;
            result[token_pos].index = index;
            result[token_pos++].value = strdup("+");
        }
        else if(input[index] == '-')
        {
            result[token_pos].type = TOKEN_MINUS;
            result[token_pos].index = index;
            result[token_pos++].value = strdup("-");
        }
        else if(input[index] == '*')
        {
            result[token_pos].type = TOKEN_STAR;
            result[token_pos].index = index;
            result[token_pos++].value = strdup("*");
        }
        else if(input[index] == '/')
        {
            if(input[index+1] == '/')
            {
                // comment case
                for(; input[index] && input[index] != '\n'; index++);
                continue;
            }
            result[token_pos].type = TOKEN_SLASH;
            result[token_pos].index = index;
            result[token_pos++].value = strdup("/");
        }


        else if(input[index] == '!')
        {
            if(input[index+1] == '=')
            {
                result[token_pos].type = TOKEN_NEQ;
                result[token_pos].index = index;
                result[token_pos++].value = strdup("!=");
                index+=1;
            }
        }

        
        else if(isspace(input[index]));

        else if(input[index] == ',')
        {
            result[token_pos].type = TOKEN_COMMA;
            result[token_pos].index = index;
            result[token_pos++].value = strdup(",");
        }
        else if(input[index] == '(')
        {
            result[token_pos].type = TOKEN_OPENING_PAREN;
            result[token_pos].index = index;
            result[token_pos++].value = strdup("(");
        }
        else if(input[index] == ')')
        {
            result[token_pos].type = TOKEN_CLOSING_PAREN;
            result[token_pos].index = index;
            result[token_pos++].value = strdup(")");
        }

        else 
        {
               
                result[token_pos].type = TOKEN_UNKNOW;
                result[token_pos].index = index;
                result[token_pos].value = malloc(2);
                result[token_pos].value[1] = 0;
                result[token_pos++].value[0] = input[index];
        }
    }
    result[token_pos].type = TOKEN_EOF;
    result[token_pos].value = malloc(1);
    result[token_pos].value[0] = 0;
    result[token_pos].index = index;
    
    Token_t* tmp = realloc(result,(token_pos+1)*sizeof(struct Token_t));
    if(tmp!=NULL)
    {
        
        return tmp;
    }
    else
    {
        perror("unable to realloc memory for tokens using old");
    }

    return result; 
}