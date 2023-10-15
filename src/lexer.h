#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "errors.h"
#include "chararray.h"


/**
 * @brief Defines the lexer_state enum which represents the different states of the lexer.
 */
typedef enum{
    STATE_START,
    STATE_IDENTIFIER_START,
    STATE_IDENTIFIER_UNDERSCORE,
    STATE_IDENTIFIER_E,
    STATE_INTEGER_E,
    STATE_INTEGER_AND_SEPARATOR,
    STATE_DOUBLE_E,
    STATE_DOUBLE_EXPONENT_START,
    STATE_DOUBLE_EXPONENT_SIGN,
    STATE_INTEGER_EXPONENT_START,
    STATE_INTEGER_EXPONENT_SIGN,
    STATE_INTEGER_EXPONENT_E,
    STATE_DOUBLE_EXPONENT_E,
    STATE_QUOTATION_CENTER_E,
    STATE_QUOTATION_ESCAPE_CHAR,
    STATE_QUOTATION_TRIPLE_E,
    STATE_SLASH,
    STATE_QUESTIONMARK,
    STATE_CLOSING_TAG,

    STATE_GT_E,      //greater than
    STATE_ST_E,      //smaller than
    STATE_EQ_E,      //first equals
    STATE_NOT,       // !
    STATE_NOT_EQ,    // !=
} lexer_state;


/**
 * @brief Struct representing a lexer object.
 * 
 * The lexer_T struct contains information about the current state of the lexer,
 * including the current character being processed, the current index in the input
 * string, and the current state of the lexer.
 */
typedef struct lexer_struct {
    char c; /* The current character being processed by the lexer. */
    unsigned int i; /* The current index in the input string. */
    lexer_state state; /* The current state of the lexer. */
} lexer_T;


/**
 * @brief Initializes a new lexer instance.
 * 
 * @return A pointer to the newly created lexer instance.
 */
lexer_T *lexer_init();

/**
 * @brief Frees the memory allocated for a lexer.
 * 
 * @param lexer The lexer to free.
 */
void lexer_free(lexer_T *lexer);

/**
 * @brief Advances the lexer to the next character in the input stream.
 * If the end of the input stream has been reached, sets the lexer's
 * current character to EOF.
 *
 * @param lexer The lexer to advance.
 */
void lexer_advance(lexer_T *lexer);

/**
 * @brief Skips the comments
 * 
 * @param lexer 
 */
void lexer_skip_comment(lexer_T *lexer);

/**
 * @brief Skips over any whitespace characters in the input stream.
 * Whitespace characters include spaces, tabs, newlines, and carriage returns.
 * 
 * @param lexer The lexer object to operate on.
 */
void lexer_skip_whitespace(lexer_T *lexer);


/**
 * @brief Get the next token from the input stream.
 * 
 * @param lexer Pointer to the lexer object.
 * @param Token Pointer to the token object to be filled with the next token.
 * @return error Returns an error code indicating success or failure.
 */
error lexer_next_token(lexer_T *lexer, token *Token);

int isoctdigit(char c);

/**
 * @brief Determines if a given string is a keyword in the language.
 * @param src The string to check.
 * @return The keyword code if the string is a keyword, otherwise 0.
 */
int is_keyword(char *src);

int str_to_int(char *src); 

double str_to_doule(char *src); 

/**
 * @brief Sanitizes the string
 * 
 * @param str 
 */
void clean_string(char **src); 

#endif