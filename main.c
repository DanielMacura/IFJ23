#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"



error ERROR = SUCCESS;

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
            lexer_next_token(lexer, Token);
            //print the current token but not as number but by its name from the enum
            printf("%s\n", token_names[Token->ID]);
        }

    }
    



    return ERROR;
} 