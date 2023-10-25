#include "grammar.h"

/**
 * @brief Define the right hand side of each production, listed back to front.
 * 
 */

int Prod0[] = {0};                 // ε
int Prod1[] = {256,257,7,260,257,6,259,5,4,258,3,257,2,1,0};                 // TOKEN_KW_FUNC TOKEN_IDENTIFIER optional_enter TOKEN_LBRACKET parameters TOKEN_RBRACKET TOKEN_ARROW type TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod2[] = {256,257,7,260,257,6,10,7,260,6,257,9,8,0};                 // TOKEN_KW_IF EXPRESSION optional_enter TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod3[] = {256,257,7,260,257,6,257,9,11,0};                 // TOKEN_KW_WHILE EXPRESSION optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod4[] = {256,262,261,12,0};                 // TOKEN_KW_RETURN return end_of_command body
int Prod5[] = {256,262,263,0};                 // function_call end_of_command body
int Prod6[] = {256,262,264,0};                 // definition end_of_command body
int Prod7[] = {256,262,265,0};                 // assignment end_of_command body
int Prod8[] = {0};                 // ε
int Prod9[] = {260,257,7,260,257,6,10,257,7,260,257,6,257,9,8,0};                 // TOKEN_KW_IF EXPRESSION optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod10[] = {260,257,7,260,257,6,257,9,11,0};                 // TOKEN_KW_WHILE EXPRESSION optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod11[] = {260,262,261,12,0};                 // TOKEN_KW_RETURN return end_of_command nested_body
int Prod12[] = {260,262,263,0};                 // function_call end_of_command nested_body
int Prod13[] = {260,262,264,0};                 // definition end_of_command nested_body
int Prod14[] = {260,262,265,0};                 // assignment end_of_command nested_body
int Prod15[] = {0};                 // ε
int Prod16[] = {257,23,0};                 // TOKEN_EOL optional_enter
int Prod17[] = {272,14,13,0};                 // TOKEN_KW_VAR TOKEN_VARIABLE definition_prime
int Prod18[] = {272,14,15,0};                 // TOKEN_KW_LET TOKEN_VARIABLE definition_prime
int Prod19[] = {275,259,16,0};                 // TOKEN_COLON type definition_prime_prime
int Prod20[] = {273,17,0};                 // TOKEN_EQUALS assignment_prime
int Prod21[] = {0};                 // ε
int Prod22[] = {273,17,0};                 // TOKEN_EQUALS assignment_prime
int Prod23[] = {273,17,14,0};                 // TOKEN_VARIABLE TOKEN_EQUALS assignment_prime
int Prod24[] = {9,0};                 // EXPRESSION
int Prod25[] = {263,0};                 // function_call
int Prod26[] = {4,271,3,2,0};                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
int Prod27[] = {269,268,0};                 // c_type postfix
int Prod28[] = {0};                 // ε
int Prod29[] = {18,0};                 // TOKEN_QUESTIONMARK
int Prod30[] = {19,0};                 // TOKEN_KW_INT
int Prod31[] = {20,0};                 // TOKEN_KW_DOUBLE
int Prod32[] = {21,0};                 // TOKEN_KW_STRING
int Prod33[] = {22,0};                 // TOKEN_KW_NIL
int Prod34[] = {23,0};                 // TOKEN_EOL
int Prod35[] = {24,0};                 // TOKEN_EOF
int Prod36[] = {270,25,0};                 // TOKEN_SEMICOLLON end_of_command_prime
int Prod37[] = {0};                 // ε
int Prod38[] = {23,0};                 // TOKEN_EOL
int Prod39[] = {0};                 // ε
int Prod40[] = {267,259,16,14,266,0};                 // discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod41[] = {0};                 // ε
int Prod42[] = {267,259,16,14,266,26,0};                 // TOKEN_COMMA discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod43[] = {14,0};                 // TOKEN_VARIABLE
int Prod44[] = {27,0};                 // TOKEN_UNDERSCORE
int Prod45[] = {0};                 // ε
int Prod46[] = {274,9,16,14,0};                 // TOKEN_VARIABLE TOKEN_COLON EXPRESSION arguments_prime
int Prod47[] = {274,9,0};                 // EXPRESSION arguments_prime
int Prod48[] = {0};                 // ε
int Prod49[] = {276,26,0};                 // TOKEN_COMMA arguments_prime_prime
int Prod50[] = {274,9,16,14,0};                 // TOKEN_VARIABLE TOKEN_COLON EXPRESSION arguments_prime
int Prod51[] = {274,9,0};                 // EXPRESSION arguments_prime
int Prod52[] = {0};                 // ε
int Prod53[] = {9,0};                 // EXPRESSION
int Prod54[] = {263,0};                 // function_call

int *productions[] = {
    Prod0, Prod1, Prod2, Prod3, Prod4, Prod5, Prod6, Prod7, Prod8, Prod9,
    Prod10, Prod11, Prod12, Prod13, Prod14, Prod15, Prod16, Prod17, Prod18, Prod19,
    Prod20, Prod21, Prod22, Prod23, Prod24, Prod25, Prod26, Prod27, Prod28, Prod29,
    Prod30, Prod31, Prod32, Prod33, Prod34, Prod35, Prod36, Prod37, Prod38, Prod39,
    Prod40, Prod41, Prod42, Prod43, Prod44, Prod45, Prod46, Prod47, Prod48, Prod49,
    Prod50, Prod51, Prod52, Prod53, Prod54
};

int table[21][29] = {
    { 1,1,5,-1,-1,-1,-1,-1,2,-1,-1,3,4,-1,6,7,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 16,15,15,15,-1,-1,15,15,15,-1,15,15,15,16,15,15,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,27,27,27,-1,-1,-1,-1,-1,-1},
    {-1,-1,12,-1,-1,-1,-1,8,9,-1,-1,10,11,-1,13,14,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,54,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,52,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,36,-1,-1,-1},
    {-1,-1,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,44,-1},
    {-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,42,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,31,32,33,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,28,-1,28,-1,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,28,29,-1,-1,-1,-1,28,28,28,-1,-1},
    { 38,37,37,-1,-1,-1,-1,37,37,-1,-1,37,37,38,37,37,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,45,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,25,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,21,21,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};

