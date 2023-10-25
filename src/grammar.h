#ifndef GRAMMAR_H
#define GRAMMAR_H

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
extern int Prod1[] ;                 // TOKEN_KW_FUNC TOKEN_IDENTIFIER TOKEN_LBRACKET parameters TOKEN_RBRACKET TOKEN_ARROW type TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET body
extern int Prod2[] ;                 // TOKEN_KW_IF EXPRESSION TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET TOKEN_KW_ELSE TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET body
extern int Prod3[] ;                 // TOKEN_KW_WHILE EXPRESSION TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET body
extern int Prod4[] ;                 // TOKEN_KW_RETURN return end_of_command body
extern int Prod5[] ;                 // function_call end_of_command body
extern int Prod6[] ;                 // definition end_of_command body
extern int Prod7[] ;                 // assignment end_of_command body
extern int Prod8[] ;                 // ε
extern int Prod9[] ;                 // TOKEN_KW_IF EXPRESSION TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET TOKEN_KW_ELSE TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET nested_body
extern int Prod10[] ;                 // TOKEN_KW_WHILE EXPRESSION TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET nested_body
extern int Prod11[] ;                 // TOKEN_KW_RETURN return end_of_command nested_body
extern int Prod12[] ;                 // function_call end_of_command nested_body
extern int Prod13[] ;                 // definition end_of_command nested_body
extern int Prod14[] ;                 // assignment end_of_command nested_body
extern int Prod15[] ;                 // TOKEN_KW_VAR TOKEN_VARIABLE definition_prime
extern int Prod16[] ;                 // TOKEN_KW_LET TOKEN_VARIABLE definition_prime
extern int Prod17[] ;                 // TOKEN_COLON type definition_prime_prime
extern int Prod18[] ;                 // TOKEN_EQUALS assignment_prime
extern int Prod19[] ;                 // ε
extern int Prod20[] ;                 // TOKEN_EQUALS assignment_prime
extern int Prod21[] ;                 // TOKEN_VARIABLE TOKEN_EQUALS assignment_prime
extern int Prod22[] ;                 // EXPRESSION
extern int Prod23[] ;                 // function_call
extern int Prod24[] ;                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
extern int Prod25[] ;                 // c_type postfix
extern int Prod26[] ;                 // ε
extern int Prod27[] ;                 // TOKEN_QUESTIONMARK
extern int Prod28[] ;                 // TOKEN_KW_extern int
extern int Prod29[] ;                 // TOKEN_KW_DOUBLE
extern int Prod30[] ;                 // TOKEN_KW_STRING
extern int Prod31[] ;                 // TOKEN_KW_NIL
extern int Prod32[] ;                 // TOKEN_EOL
extern int Prod33[] ;                 // TOKEN_EOF
extern int Prod34[] ;                 // TOKEN_SEMICOLLON end_fo_command_prime
extern int Prod35[] ;                 // ε
extern int Prod36[] ;                 // TOKEN_EOL
extern int Prod37[] ;                 // ε
extern int Prod38[] ;                 // TOKEN_VARIABLE TOKEN_VARIABLE TOKEN_COLON type parameters_prime
extern int Prod39[] ;                 // ε
extern int Prod40[] ;                 // TOKEN_COMMA TOKEN_VARIABLE TOKEN_VARIABLE TOKEN_COLON type parameters_prime
extern int Prod41[] ;                 // ε
extern int Prod42[] ;                 // TOKEN_VARIABLE TOKEN_COLON EXPRESSION arguments_prime
extern int Prod43[] ;                 // EXPRESSION arguments_prime
extern int Prod44[] ;                 // ε
extern int Prod45[] ;                 // TOKEN_COMMA arguments_prime_prime
extern int Prod46[] ;                 // ε
extern int Prod47[] ;                 // TOKEN_VARIABLE TOKEN_COLON EXPRESSION arguments_prime
extern int Prod48[] ;                 // EXPRESSION arguments_prime
extern int Prod49[] ;                 // ε
extern int Prod50[] ;                 // EXPRESSION
extern int Prod51[] ;                 // function_call
extern int Prod52[] ;                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
extern int Prod53[] ;                 // c_type postfix
extern int Prod54[] ;                 // ε

extern int *productions[];

extern int table[21][29];

#endif
