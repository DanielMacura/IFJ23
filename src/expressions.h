
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "DLL.h"
#include "lexer.h"
#include "symtable.h"
#include "token.h"
#include "errors.h"
#include "analyser.h"


/**
 * @brief Macro wrapper for creating new item for the stack.
 *        If the item cant be created, free the stack and return error.
 */
#define new_item(new_item, token_ptr, type)     \
    new_item = expr_item_new(token_ptr, type);  \
    if (!new_item) {                            \
        expr_stack_free(expr_stack);            \
        return INTERNAL_ERR;                    \
    }


/**
 * @brief Macro for getting next token from the input
 *        and pushing it to the end of the list.
 *        If the last element of the list isnt the active one,
 *        a token was returned and we need to move the active element to the right
 *        and take the token again. 
 *        Also counts the number of tokens taken which may all be returned by return_all_tokens().
 *        EOL tokens are ignored.
 */
#define next_token_counted()                                \
    ;                                                       \
    if (dll->activeElement == dll->lastElement)             \
    {                                                       \
        do                                                  \
        {                                                   \
            token_ptr = calloc(1, sizeof(*token_ptr));      \
            ERROR = lexer_next_token(lexer, token_ptr);     \
                DLL_push(dll, token_ptr);                   \
            if (token_ptr->ID != TOKEN_EOL)                 \
            {                                               \
                COUNTER++;                                  \
            }                                               \
        } while (token_ptr->ID == TOKEN_EOL);               \
    }                                                       \
    else                                                    \
    {                                                       \
        do                                                  \
        {                                                   \
            DLL_move_active_right(dll);                     \
            token_ptr = DLL_get_active(dll);                \
            if (token_ptr->ID != TOKEN_EOL)                 \
            {                                               \
                COUNTER++;                                  \
            }                                               \
        } while (token_ptr->ID == TOKEN_EOL);               \
    }                                                       \


/**
 * @brief Macro for returning all tokens taken by next_token().
 *        Used when an error occurs and we need to return all tokens taken
 *        for syntax analysis to continue.
 */
#define return_all_tokens()              \
    ;                                    \
    for (size_t i = 0; i < COUNTER; i++) \
    {                                    \
        DLL_move_active_left(dll);       \
    }                                    \
    COUNTER = 0;

typedef enum {
    TERM,
    NONTERM,
    DOLLAR
} expr_item_type;

typedef enum {
    UNDEFINED,
    NULL_TYPE,
    INT,
    INT_NULL,
    FLOAT,
    FLOAT_NULL,
    STRING,
    STRING_NULL,
    BOOL_TYPE,
    TERM_TYPE,       //INT, FLOAT or STRING
    
} data_type;

typedef struct expr_item {
    token *token_ptr;
    expr_item_type type;
    data_type data_type; // non terminal only
    bool breakpoint;
    struct expr_item *next_item;
} expr_item;

typedef struct {
    int size;
    expr_item *top_item;
} expr_stack;

/**
 * @brief 
 * 
 */
typedef enum rules{
    PAR_E_PAR,      // E -> (E)
    E_PLUS_E,       // E -> E + E
    E_MINUS_E,      // E -> E - E
    E_MULTIPLE_E,   // E -> E * E
    E_DIVIDE_E,     // E -> E / E
    E_EQ_E,         // E -> E == E
    E_NEQ_E,        // E -> E != E
    E_LT_E,         // E -> E < E
    E_GT_E,         // E -> E > E
    E_LEQ_E,        // E -> E <= E
    E_GEQ_E,        // E -> E >= E
    E_COALESCE_E,   // E -> E ?? E
    E_EXCLAMATION,  // E -> E!
    ID,             // E -> id
    NONE            // No rule
} rules;

expr_item *expr_item_new(token *, expr_item_type);

expr_stack *expr_stack_new();

void expr_stack_push(expr_stack *, expr_item *);

expr_item *expr_stack_pop(expr_stack *);

void expr_stack_free(expr_stack *);

char get_precedence(token *, token *);

int count_breakpoint(expr_stack *);

//FIXME data_type get_data_type_from_item(expr_item *, expr_item *, expr_item */*, symtables*/);    //TODO: add symtables

bool apply_rule(expr_stack */*, symtables*/);   //TODO: add symtables

expr_item *get_term_or_dollar(expr_stack *);

bool parse_expression(lexer_T *, DLL *,/*symtables,*/ data_type *, bool);   //TODO: add symtables

static const char precedence_table[9][9]={
//       (    )    !    *    +   ==   ??    i    $
/* ( */{'<', '=', '<', '<', '<', '<', '<', '<', '\0'},
/* ) */{'\0','>', '>', '>', '>', '>', '>', '\0','>' },
/* ! */{'<', '>', '\0','>', '>', '>', '>', '<', '>' },
/* * */{'<', '>', '<', '>', '>', '>', '>', '<', '>' },
/* + */{'<', '>', '<', '<', '>', '>', '>', '<', '>' },
/* ==*/{'<', '>', '<', '<', '<', '\0','>', '<', '>' },
/* ??*/{'<', '>', '<', '<', '<', '<', '<', '<', '>' },
/* i */{'\0','>', '>', '>', '>', '>', '>', 'i', '>' },
/* $ */{'<', '\0','<', '<', '<', '<', '<', '<', 'f'}
};


#endif