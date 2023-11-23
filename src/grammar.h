/**
 * @file grammar.h
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Header file for grammar.c
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "errors.h"
#include "lexer.h"
#include "expressions.h"
#include "types.h"
#include "symtable.h"


#define MINTERM 1       /* Smallest terminal. */
#define MAXTERM 255       /* Largest terminal. */
#define MINNONTERM 256  /* Smallest nonterminal. */
#define MAXNONTERM 400  /* Largest nonterminal. */
#define STARTSTATE 256 /* Goal symbol (push to startparse) */
#define MINACT 512      /* Smallest action. */

#define ISTERM(x) ((x) >= MINTERM && (x) <= MAXTERM)
#define ISNONTERM(x) ((x) >= MINNONTERM && (x) <= MAXNONTERM)
#define ISACT(x) ((x) >= MINACT)




/**
 * @brief Define the right hand side of each production, listed back to front.
 * 
 */
extern int Prod0[] ;                 // ε
extern int Prod1[] ;                 // TOKEN_KW_FUNC TOKEN_IDENTIFIER optional_enter TOKEN_LBRACKET parameters TOKEN_RBRACKET TOKEN_ARROW type TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
extern int Prod2[] ;                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
extern int Prod3[] ;                 // TOKEN_KW_WHILE expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
extern int Prod4[] ;                 // TOKEN_KW_RETURN return end_of_command body
extern int Prod5[] ;                 // function_call end_of_command body
extern int Prod6[] ;                 // definition end_of_command body
extern int Prod7[] ;                 // assignment end_of_command body
extern int Prod8[] ;                 // ε
extern int Prod9[] ;                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
extern int Prod10[] ;                 // TOKEN_KW_WHILE expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
extern int Prod11[] ;                 // TOKEN_KW_RETURN return end_of_command nested_body
extern int Prod12[] ;                 // function_call end_of_command nested_body
extern int Prod13[] ;                 // definition end_of_command nested_body
extern int Prod14[] ;                 // assignment end_of_command nested_body
extern int Prod15[] ;                 // ε
extern int Prod16[] ;                 // TOKEN_EOL optional_enter
extern int Prod17[] ;                 // TOKEN_KW_VAR TOKEN_VARIABLE definition_prime
extern int Prod18[] ;                 // TOKEN_KW_LET TOKEN_VARIABLE definition_prime
extern int Prod19[] ;                 // TOKEN_COLON type definition_prime_prime
extern int Prod20[] ;                 // TOKEN_EQUALS assignment_prime
extern int Prod21[] ;                 // ε
extern int Prod22[] ;                 // TOKEN_EQUALS assignment_prime
extern int Prod23[] ;                 // TOKEN_VARIABLE TOKEN_EQUALS assignment_prime
extern int Prod24[] ;                 // expression
extern int Prod25[] ;                 // function_call
extern int Prod26[] ;                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
extern int Prod27[] ;                 // c_type postfix
extern int Prod28[] ;                 // ε
extern int Prod29[] ;                 // TOKEN_QUESTIONMARK
extern int Prod30[] ;                 // TOKEN_KW_INT
extern int Prod31[] ;                 // TOKEN_KW_DOUBLE
extern int Prod32[] ;                 // TOKEN_KW_STRING
extern int Prod33[] ;                 // TOKEN_KW_NIL
extern int Prod34[] ;                 // TOKEN_EOL
extern int Prod35[] ;                 // TOKEN_EOF
extern int Prod36[] ;                 // TOKEN_SEMICOLLON end_of_command_prime
extern int Prod37[] ;                 // ε
extern int Prod38[] ;                 // TOKEN_EOL
extern int Prod39[] ;                 // ε
extern int Prod40[] ;                 // discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
extern int Prod41[] ;                 // ε
extern int Prod42[] ;                 // TOKEN_COMMA discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
extern int Prod43[] ;                 // TOKEN_VARIABLE
extern int Prod44[] ;                 // TOKEN_UNDERSCORE
extern int Prod45[] ;                 // ε
extern int Prod46[] ;                 // TOKEN_VARIABLE arguments_var
extern int Prod47[] ;                 // literal arguments_lit
extern int Prod48[] ;                 // TOKEN_VARIABLE arguments_var
extern int Prod49[] ;                 // literal arguments_lit
extern int Prod50[] ;                 // ε
extern int Prod51[] ;                 // TOKEN_COMMA arguments_prime
extern int Prod52[] ;                 // TOKEN_COLON literal arguments
extern int Prod53[] ;                 // ε
extern int Prod54[] ;                 // TOKEN_COMMA arguments_prime
extern int Prod55[] ;                 // ε
extern int Prod56[] ;                 // expression
extern int Prod57[] ;                 // function_call
extern int Prod58[] ;                 // TOKEN_INTEGER
extern int Prod59[] ;                 // TOKEN_FLOAT
extern int Prod60[] ;                 // TOKEN_STRING
extern int Prod61[] ;                 // TOKEN_KW_NIL
extern int Prod62[] ;                 // TOKEN_VARIABLE
extern int Prod63[] ;                 // TOKEN_INTEGER
extern int Prod64[] ;                 // TOKEN_FLOAT
extern int Prod65[] ;                 // TOKEN_STRING
extern int Prod66[] ;                 // TOKEN_PLUS
extern int Prod67[] ;                 // TOKEN_MINUS
extern int Prod68[] ;                 // TOKEN_DOUBLE_EQUALS
extern int Prod69[] ;                 // TOKEN_NOT_EQUALS
extern int Prod70[] ;                 // TOKEN_GT
extern int Prod71[] ;                 // TOKEN_LT
extern int Prod72[] ;                 // TOKEN_GTE
extern int Prod73[] ;                 // TOKEN_LTE
extern int Prod74[] ;                 // TOKEN_NIL_COALESCING
extern int Prod75[] ;                 // TOKEN_DIVISION
extern int Prod76[] ;                 // TOKEN_MULTIPLICATION
extern int Prod77[] ;                 // TOKEN_LBRACKET
extern int Prod78[] ;                 // TOKEN_RBRACKET
extern int Prod79[] ;                 // TOKEN_ARROW
extern int Prod80[] ;                 // TOKEN_LCURLYBRACKET

int actions(int action_num, DLL *dll, DLLElementPtr ptr_before_expression, data_type *final_type);

extern int *productions[];

extern int table[24][43];

#endif
