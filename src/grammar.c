/**
 * @file grammar.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of grammar used in table parser
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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
int Prod6[] = {256,263,513,265,0};                 // definition end_of_command body
int Prod7[] = {256,263,513,266,0};                 // assignment end_of_command body
int Prod8[] = {0};                 // ε
int Prod9[] = {260,257,7,260,257,6,9,257,7,260,257,6,257,261,8,0};                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod10[] = {260,257,7,260,257,6,257,261,10,0};                 // TOKEN_KW_WHILE expression optional_enter TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET optional_enter nested_body
int Prod11[] = {260,263,262,11,0};                 // TOKEN_KW_RETURN return end_of_command nested_body
int Prod12[] = {260,263,264,0};                 // function_call end_of_command nested_body
int Prod13[] = {260,263,513,265,0};                 // definition end_of_command nested_body
int Prod14[] = {260,263,513,266,0};                 // assignment end_of_command nested_body
int Prod15[] = {0};                 // ε
int Prod16[] = {257,12,0};                 // TOKEN_EOL optional_enter
int Prod17[] = {273,14,512,13,0};                 // TOKEN_KW_VAR TOKEN_VARIABLE definition_prime
int Prod18[] = {273,14,512,15,0};                 // TOKEN_KW_LET TOKEN_VARIABLE definition_prime
int Prod19[] = {278,259,16,0};                 // TOKEN_COLON type definition_prime_prime
int Prod20[] = {274,17,0};                 // TOKEN_EQUALS assignment_prime
int Prod21[] = {0};                 // ε
int Prod22[] = {274,17,0};                 // TOKEN_EQUALS assignment_prime
int Prod23[] = {274,17,14,0};                 // TOKEN_VARIABLE TOKEN_EQUALS assignment_prime
int Prod24[] = {261,0};                 // expression
int Prod25[] = {264,0};                 // function_call
int Prod26[] = {4,272,3,2,0};                 // TOKEN_IDENTIFIER TOKEN_LBRACKET arguments TOKEN_RBRACKET
int Prod27[] = {270,269,0};                 // c_type postfix
int Prod28[] = {0};                 // ε
int Prod29[] = {18,0};                 // TOKEN_QUESTIONMARK
int Prod30[] = {19,0};                 // TOKEN_KW_INT
int Prod31[] = {20,0};                 // TOKEN_KW_DOUBLE
int Prod32[] = {21,0};                 // TOKEN_KW_STRING
int Prod33[] = {22,0};                 // TOKEN_KW_NIL
int Prod34[] = {12,0};                 // TOKEN_EOL
int Prod35[] = {23,0};                 // TOKEN_EOF
int Prod36[] = {271,24,0};                 // TOKEN_SEMICOLLON end_of_command_prime
int Prod37[] = {0};                 // ε
int Prod38[] = {12,0};                 // TOKEN_EOL
int Prod39[] = {0};                 // ε
int Prod40[] = {268,259,16,14,267,0};                 // discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod41[] = {0};                 // ε
int Prod42[] = {268,259,16,14,267,25,0};                 // TOKEN_COMMA discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type parameters_prime
int Prod43[] = {14,0};                 // TOKEN_VARIABLE
int Prod44[] = {26,0};                 // TOKEN_UNDERSCORE
int Prod45[] = {0};                 // ε
int Prod46[] = {275,14,0};                 // TOKEN_VARIABLE arguments_var
int Prod47[] = {277,276,0};                 // literal arguments_lit
int Prod48[] = {275,14,0};                 // TOKEN_VARIABLE arguments_var
int Prod49[] = {277,276,0};                 // literal arguments_lit
int Prod50[] = {0};                 // ε
int Prod51[] = {279,25,0};                 // TOKEN_COMMA arguments_prime
int Prod52[] = {272,276,16,0};                 // TOKEN_COLON literal arguments
int Prod53[] = {0};                 // ε
int Prod54[] = {279,25,0};                 // TOKEN_COMMA arguments_prime
int Prod55[] = {0};                 // ε
int Prod56[] = {261,0};                 // expression
int Prod57[] = {264,0};                 // function_call
int Prod58[] = {27,0};                 // TOKEN_INTEGER
int Prod59[] = {28,0};                 // TOKEN_FLOAT
int Prod60[] = {29,0};                 // TOKEN_STRING
int Prod61[] = {22,0};                 // TOKEN_KW_NIL
int Prod62[] = {14,0};                 // TOKEN_VARIABLE
int Prod63[] = {27,0};                 // TOKEN_INTEGER
int Prod64[] = {28,0};                 // TOKEN_FLOAT
int Prod65[] = {29,0};                 // TOKEN_STRING
int Prod66[] = {30,0};                 // TOKEN_PLUS
int Prod67[] = {31,0};                 // TOKEN_MINUS
int Prod68[] = {32,0};                 // TOKEN_DOUBLE_EQUALS
int Prod69[] = {33,0};                 // TOKEN_NOT_EQUALS
int Prod70[] = {34,0};                 // TOKEN_GT
int Prod71[] = {35,0};                 // TOKEN_LT
int Prod72[] = {36,0};                 // TOKEN_GTE
int Prod73[] = {37,0};                 // TOKEN_LTE
int Prod74[] = {38,0};                 // TOKEN_NIL_COALESCING
int Prod75[] = {39,0};                 // TOKEN_DIVISION
int Prod76[] = {40,0};                 // TOKEN_MULTIPLICATION
int Prod77[] = {3,0};                 // TOKEN_LBRACKET
int Prod78[] = {4,0};                 // TOKEN_RBRACKET
int Prod79[] = {22,0};                 // TOKEN_KW_NIL
int Prod80[] = {41,0};                 // TOKEN_EXCLAMATIONMARK
int Prod81[] = {256, 12, 0};                 // body

int *productions[] = {
    Prod0, Prod1, Prod2, Prod3, Prod4, Prod5, Prod6, Prod7, Prod8, Prod9,
    Prod10, Prod11, Prod12, Prod13, Prod14, Prod15, Prod16, Prod17, Prod18, Prod19,
    Prod20, Prod21, Prod22, Prod23, Prod24, Prod25, Prod26, Prod27, Prod28, Prod29,
    Prod30, Prod31, Prod32, Prod33, Prod34, Prod35, Prod36, Prod37, Prod38, Prod39,
    Prod40, Prod41, Prod42, Prod43, Prod44, Prod45, Prod46, Prod47, Prod48, Prod49,
    Prod50, Prod51, Prod52, Prod53, Prod54, Prod55, Prod56, Prod57, Prod58, Prod59,
    Prod60, Prod61, Prod62, Prod63, Prod64, Prod65, Prod66, Prod67, Prod68, Prod69,
    Prod70, Prod71, Prod72, Prod73, Prod74, Prod75, Prod76, Prod77, Prod78, Prod79,
    Prod80, Prod81
};

int actions(int action_num, DLL *dll, DLLElementPtr ptr_before_expression){
    DLLElementPtr activeElement = dll->activeElement; //remember active element
    int should_push_value_to_variable = 0;

    switch (action_num)
    {
        /**
         * @brief Define a variable with a given name.
         * 
         */
        case 512:
            defineVariable(dll->activeElement->data.VAL.string);
            break;
        /**
         * @brief Push a value from the stack (from expression parser) to a variable.
         *        Search from the beginning of the expression for the variable token,
         *        to get the name of the variable. If a 
         */
        case 513:
            
            dll->activeElement = ptr_before_expression; //go to the first element of the expression and look for variable token
            DLL_move_active_left(dll);  //get first token before expression

            while (dll->activeElement->previousElement != NULL)
            {
                if (dll->activeElement->data.ID == TOKEN_VARIABLE)
                {
                    break;
                }
                if (dll->activeElement->data.ID == TOKEN_EQUALS)
                {
                    should_push_value_to_variable = 1;
                }
                DLL_move_active_left(dll);
            }


            if (should_push_value_to_variable){
                popToVariable(dll->activeElement->data.VAL.string);
            }

            dll->activeElement = activeElement;    //return to active element

            break;

    default:
        return SYNTAX_ERR;
        break;
    }
    return SUCCESS;
}
int table[24][43] = {
    { 1,1,5,-1,-1,-1,-1,-1,2,-1,3,4,81,6,7,6,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 16,15,15,15,-1,-1,15,15,15,15,15,15,16,15,15,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,27,27,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,12,-1,-1,-1,-1,8,9,-1,10,11,-1,13,14,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,77,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,-1,-1,-1,-1,79,-1,-1,-1,-1,63,64,65,66,67,68,69,70,71,72,73,74,75,76,80,-1},
    {-1,-1,57,56,56,-1,-1,-1,-1,-1,-1,-1,55,-1,56,-1,-1,-1,-1,-1,-1,-1,56,55,55,-1,-1,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,36,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,17,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,42,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,30,31,32,33,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,28,-1,28,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,28,29,-1,-1,-1,-1,28,28,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 38,37,37,-1,-1,-1,-1,37,37,-1,37,37,38,37,37,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,46,-1,-1,-1,-1,-1,-1,-1,47,-1,-1,-1,-1,47,47,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,25,24,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,-1},
    {-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,-1,-1,-1,-1,58,59,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,21,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,49,49,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};
