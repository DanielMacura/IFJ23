#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

/**
 * @brief Main function of the compiler
 * 
 * @return int 
 */
const char *token_names[] = {
        "IDENTIFIER",
        "VARIABLE",
        "INTEGER",
        "FLOAT",
        "STRING",
        "KEYWORD",
        "PLUS",
        "MINUS",
        "EQUALS",
        "DOUBLE_EQUALS",
        "NOT_EQUALS",
        "GT",
        "LT",
        "GTE",
        "LTE",
        "QUESTIONMARK",
        "NIL_COALESCING",
        "EXCLAMATIONMARK",
        "DIVISION",
        "MULTIPLICATION",
        "COMMA",
        "SEMICOLLON",
        "COLON",
        "LBRACKET",
        "RBRACKET",
        "LCURLYBRACKET",
        "RCURLYBRACKET",
        "EOL",
        "EOF"
    };
int main(int argc, char **argv) {
    lexer_T *lexer = lexer_init();
    token *Token = malloc(sizeof(token));

    // Lexer tests, generates tokens from the input
    if (argc == 2 && strcmp(argv[1], "-t") == 0)
    {
        while (Token->ID != TOKEN_ID_EOF)
        {
            int return_code = lexer_next_token(lexer, Token);
            if (return_code != SUCCESS)
            {
                printf("Error code: %d\n", return_code);
                return return_code;
            }
            switch (Token->ID) {
                case TOKEN_ID_INTEGER:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                case TOKEN_ID_STRING:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                case TOKEN_ID_FLOAT:
                    printf("%s:%s\n", token_names[Token->ID], Token->VAL.string);
                    break;
                default:
                    printf("%s\n", token_names[Token->ID]);
            }
        }

    }
} 