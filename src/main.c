#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include <unistd.h>
#include "token.h"
#include "stack.h"
#include "analyser.h"
#include "errors.h"
#include "chararray.h"


/**
 * @brief Main function of the compiler
 * 
 * @return int 
 */

int main(int argc, char **argv) {
    lexer_T *lexer = lexer_init();
    token *Token = malloc(sizeof(token));

    // Lexer tests, generates tokens from the input
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {        
        do 
        {
            int return_code = lexer_next_token(lexer, Token);
            if (return_code != SUCCESS)
            {
                printf("Error code: %d\n", return_code);
                return return_code;
            }
            switch (Token->ID) {
                case TOKEN_INTEGER:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                case TOKEN_STRING:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                case TOKEN_FLOAT:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                default:
                    printf("%s\n", token_names[Token->ID]);
            }
        } while (Token->ID != TOKEN_EOF);
    }
} 