/**
 * @file types.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for storing types to avoid circular dependencies
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef TYPES_H
#define TYPES_H

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

typedef enum rules{
    PAR_E_PAR,      // E -> (E)
    E_PLUS_E,       // E -> E + E
    E_MINUS_E,      // E -> E - E
    E_CONCAT_E,     // E -> E + E
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

#endif