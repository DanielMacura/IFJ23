#include "token.h"

/**
 * @brief Array of token names.
 * 
 * This array contains the names of all tokens, in the same order as the token enum.
 * Used for debugging purposes.
 */
const char *token_names[] = {
    "EPSILON",
    "KW_FUNC",
    "IDENTIFIER",
    "LBRACKET",
    "RBRACKET",
    "ARROW",
    "LCURLYBRACKET",
    "RCURLYBRACKET",
    "KW_IF",
    "EXPRESSION",
    "KW_ELSE",
    "KW_WHILE",
    "KW_RETURN",
    "KW_VAR",
    "VARIABLE",
    "KW_LET",
    "COLON",
    "EQUALS",
    "QUESTIONMARK",
    "KW_INT",
    "KW_DOUBLE",
    "KW_STRING",
    "KW_NIL",
    "EOL",
    "EOF",
    "SEMICOLLON",
    "COMMA",

    "INTEGER",
    "FLOAT",
    "STRING",
    "PLUS",
    "MINUS",
    "DOUBLE_EQUALS",
    "NOT_EQUALS",
    "GT",          
    "LT",            
    "GTE",             
    "LTE",    
    "NIL_COALESCING",  
    "EXCLAMATIONMARK",
    "DIVISION",
    "MULTIPLICATION"
};
