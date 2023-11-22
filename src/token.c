/**
 * @file token.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Stores token names for debugging purposes
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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
    "KW_ELSE",
    "KW_WHILE",
    "KW_RETURN",
    "EOL",
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
    "EOF",
    "SEMICOLLON",
    "COMMA",
    "TOKEN_UNDERSCORE",

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
    "DIVISION",
    "MULTIPLICATION",
    "EXCLAMATIONMARK",
};
