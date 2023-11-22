/**
 * @file analyzer.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for analyzer.c
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ANALYSER_H
#define ANALYSER_H

#include "grammar.h"
#include "lexer.h"
#include "token.h"
#include "stack.h"
#include "DLL.h"
#include "errors.h"
#include "expressions.h"
#include "generator.h"
#include "verbose.h"

extern int table[24][43] ;
extern int *productions[];

/**
 * @brief Macro for getting next token from the input
 *        and pushing it to the end of the list.
 *        If the last element of the list isnt the active one,
 *        a token was returned and we need to move the active element to the right
 *        and take the token again. 
 */
#define next_token()                                \
    ;                                               \
    if (dll->activeElement == dll->lastElement)     \
    {                                               \
        token_ptr = calloc(1, sizeof(*token_ptr));  \
        ERROR = lexer_next_token(lexer, token_ptr); \
        DLL_push(dll, token_ptr);                   \
    }                                               \
    else                                            \
    {                                               \
        DLL_move_active_right(dll);                 \
        token_ptr = DLL_get_active(dll);            \
    }

/**
 * @brief Macro for returning the token to the input.
 *        May be again taken by next_tok()
 * 
 */
#define return_token() \
    ;                  \
    DLL_move_active_left(dll);

/**
 * @brief Runs the top-down syntax analysis using the LL(1) table
 * 
 * @param lexer 
 * @param dll 
 * @return int 
 */
int runSyntax(lexer_T *lexer, DLL *dll);

#endif
