#include "grammar.h"

/**
 * @brief Define the right hand side of each production, listed back to front.
 * 
 */

int Prod0[] = {0};                 // ε
int Prod1[] = {256,257,7,260,257,6,259,5,4,258,3,257,2,1,0};                 // TOKEN_KW_FUNC TOKEN_IDENTIFIER optional_enter TOKEN_LBRACKET parameters TOKEN_RBRACKET TOKEN_ARROW type TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod2[] = {256,257,7,260,257,6,9,7,260,6,257,261,8,0};                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET nested_body TOKEN_RCURLYBRACKET TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod3[] = {256,257,7,260,257,6,257,261,10,0};                 // TOKEN_KW_WHILE expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter body
int Prod4[] = {256,263,262,11,0};                 // TOKEN_KW_RETURN return end_of_command body
int Prod5[] = {256,263,264,0};                 // function_call end_of_command body
int Prod6[] = {256,263,265,0};                 // definition end_of_command body
int Prod7[] = {256,263,266,0};                 // assignment end_of_command body
int Prod8[] = {12,0};                 // TOKEN_EOF
int Prod9[] = {0};                 // ε
int Prod10[] = {260,257,7,260,257,6,9,257,7,260,257,6,257,261,8,0};                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod11[] = {260,257,7,260,257,6,257,261,10,0};                 // TOKEN_KW_WHILE expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod12[] = {260,263,262,11,0};                 // TOKEN_KW_RETURN return end_of_command nested_body
int Prod13[] = {260,263,264,0};                 // function_call end_of_command nested_body
int Prod14[] = {260,263,265,0};                 // definition end_of_command nested_body
int Prod15[] = {260,263,266,0};                 // assignment end_of_command nested_body
int Prod16[] = {0};                 // ε
int Prod17[] = {257,13,0};                 // TOKEN_EOL optional_enter
int Prod18[] = {273,15,14,0};                 // TOKEN_KW_VAR TOKEN_VARIABLE definition_prime
int Prod19[] = {273,15,16,0};                 // TOKEN_KW_LET TOKEN_VARIABLE definition_prime
int Prod20[] = {278,259,17,0};                 // TOKEN_COLON type definition_prime_prime
int Prod21[] = {274,18,0};                 // TOKEN_EQUALS assignment_prime
int Prod22[] = {0};                 // ε
int Prod23[] = {274,18,0};                 // TOKEN_EQUALS assignment_prime
int Prod24[] = {274,18,15,0};                 // TOKEN_VARIABLE TOKEN_EQUALS assignment_prime
int Prod25[] = {261,0};                 // expression
int Prod26[] = {264,0};                 // function_call
int Prod27[] = {4,272,3,2,0};                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
int Prod28[] = {270,269,0};                 // c_type postfix
int Prod29[] = {0};                 // ε
int Prod30[] = {19,0};                 // TOKEN_QUESTIONMARK
int Prod31[] = {20,0};                 // TOKEN_KW_INT
int Prod32[] = {21,0};                 // TOKEN_KW_DOUBLE
int Prod33[] = {22,0};                 // TOKEN_KW_STRING
int Prod34[] = {23,0};                 // TOKEN_KW_NIL
int Prod35[] = {13,0};                 // TOKEN_EOL
int Prod36[] = {12,0};                 // TOKEN_EOF
int Prod37[] = {271,24,0};                 // TOKEN_SEMICOLLON end_of_command_prime
int Prod38[] = {0};                 // ε
int Prod39[] = {13,0};                 // TOKEN_EOL
int Prod40[] = {0};                 // ε
int Prod41[] = {268,259,17,15,267,0};                 // discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod42[] = {0};                 // ε
int Prod43[] = {268,259,17,15,267,25,0};                 // TOKEN_COMMA discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod44[] = {15,0};                 // TOKEN_VARIABLE
int Prod45[] = {26,0};                 // TOKEN_UNDERSCORE
int Prod46[] = {0};                 // ε
int Prod47[] = {275,15,0};                 // TOKEN_VARIABLE arguments_var
int Prod48[] = {277,276,0};                 // literal arguments_lit
int Prod49[] = {275,15,0};                 // TOKEN_VARIABLE arguments_var
int Prod50[] = {277,276,0};                 // literal arguments_lit
int Prod51[] = {0};                 // ε
int Prod52[] = {279,25,0};                 // TOKEN_COMMA arguments_prime
int Prod53[] = {272,276,17,0};                 // TOKEN_COLON literal arguments
int Prod54[] = {0};                 // ε
int Prod55[] = {279,25,0};                 // TOKEN_COMMA arguments_prime
int Prod56[] = {0};                 // ε
int Prod57[] = {261,0};                 // expression
int Prod58[] = {264,0};                 // function_call
int Prod59[] = {27,0};                 // TOKEN_INTEGER
int Prod60[] = {28,0};                 // TOKEN_FLOAT
int Prod61[] = {29,0};                 // TOKEN_STRING
int Prod62[] = {23,0};                 // TOKEN_KW_NIL
int Prod63[] = {15,0};                 // TOKEN_VARIABLE
int Prod64[] = {27,0};                 // TOKEN_INTEGER
int Prod65[] = {28,0};                 // TOKEN_FLOAT
int Prod66[] = {29,0};                 // TOKEN_STRING
int Prod67[] = {30,0};                 // TOKEN_PLUS
int Prod68[] = {31,0};                 // TOKEN_MINUS
int Prod69[] = {32,0};                 // TOKEN_DOUBLE_EQUALS
int Prod70[] = {33,0};                 // TOKEN_NOT_EQUALS
int Prod71[] = {34,0};                 // TOKEN_GT
int Prod72[] = {35,0};                 // TOKEN_LT
int Prod73[] = {36,0};                 // TOKEN_GTE
int Prod74[] = {37,0};                 // TOKEN_LTE
int Prod75[] = {38,0};                 // TOKEN_NIL_COALESCING
int Prod76[] = {39,0};                 // TOKEN_DIVISION
int Prod77[] = {40,0};                 // TOKEN_MULTIPLICATION
int Prod78[] = {3,0};                 // TOKEN_LBRACKET
int Prod79[] = {4,0};                 // TOKEN_RBRACKET
int *productions[] = {
    Prod0, Prod1, Prod2, Prod3, Prod4, Prod5, Prod6, Prod7, Prod8, Prod9,
    Prod10, Prod11, Prod12, Prod13, Prod14, Prod15, Prod16, Prod17, Prod18, Prod19,
    Prod20, Prod21, Prod22, Prod23, Prod24, Prod25, Prod26, Prod27, Prod28, Prod29,
    Prod30, Prod31, Prod32, Prod33, Prod34, Prod35, Prod36, Prod37, Prod38, Prod39,
    Prod40, Prod41, Prod42, Prod43, Prod44, Prod45, Prod46, Prod47, Prod48, Prod49,
    Prod50, Prod51, Prod52, Prod53, Prod54, Prod55, Prod56, Prod57, Prod58, Prod59,
    Prod60, Prod61, Prod62, Prod63, Prod64, Prod65, Prod66, Prod67, Prod68, Prod69,
    Prod70, Prod71, Prod72, Prod73, Prod74, Prod75, Prod76, Prod77, Prod78, Prod79,
};
int table[24][42] = {
    { 1,1,5,-1,-1,-1,-1,-1,2,-1,3,4,8,-1,6,7,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 17,16,16,16,-1,-1,16,16,16,16,16,16,16,17,16,16,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,28,28,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,13,-1,-1,-1,-1,9,10,-1,11,12,-1,-1,14,15,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,78,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,63,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,65,66,67,68,69,70,71,72,73,74,75,76,77,-1},
    {-1,-1,58,57,57,-1,-1,-1,-1,-1,-1,-1,56,56,-1,57,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,-1,57,57,57,57,57,57,57,57,57,57,57,57,57,57,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,-1,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,42,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,32,33,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,29,-1,29,-1,-1,-1,-1,-1,29,29,-1,-1,-1,-1,29,30,-1,-1,-1,-1,29,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 39,38,38,-1,-1,-1,-1,38,38,-1,38,38,38,39,38,38,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,48,48,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,26,25,25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,25,25,25,25,25,25,25,25,25,25,25,25,25,-1},
    {-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,59,60,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,22,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,50,-1,-1,-1,50,50,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};

