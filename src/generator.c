/**
 * @file generator.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of generator, used in actions and expressions
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "generator.h"

extern int argument_counter;

void beginGenerator(){
    printf(".IFJcode23\n");

    printf("JUMP $$main\n");
    
    generateBuiltin();

    beginMain();
}

void generateBuiltin(){
    builtin_write();
}

void endGenerator(){
    printf("LABEL $$end\n");
    printf("EXIT int@0\n");
}

void beginMain(){
    printf("LABEL $$main\n");
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
}

void endMain(){
    printf("LABEL $$main_end\n");
    printf("POPFRAME\n");
}

void defineVariable(char *name){
    printf("DEFVAR LF@%s\n", name);
}

void generateConstant(char *name, data_type type, char *value){
    printf("DEFVAR LF@%s\n", name);
    switch (type)
    {
    case INT_NULL:
    case INT:
        printf("MOVE LF@%s int@0\n", name);
        break;
    case FLOAT_NULL:
    case FLOAT:
        printf("MOVE LF@%s float@0.0\n", name);
        break;
    case STRING_NULL:
    case STRING:
        printf("MOVE LF@%s string@\n", name);
        break;
    case NULL_TYPE:
        printf("MOVE LF@%s nil@nil\n", name);
        break;
    default:
        break;
    }
}

void popToVariable(char *name) {
    printf("POPS LF@%s\n", name);
}

void generateTerm(token *token_ptr) {

    if (token_ptr->ID == TOKEN_INTEGER) {
        printf("int@%s", token_ptr->VAL.string);
    }
    else if (token_ptr->ID == TOKEN_FLOAT) {
        printf("float@%a", atof(token_ptr->VAL.string));
    }
    else if (token_ptr->ID == TOKEN_STRING) {
        printf("string@%s", token_ptr->VAL.string);
    }
    else if (token_ptr->ID == TOKEN_VARIABLE) {
        printf("LF@%s", token_ptr->VAL.string);
    }
}

void operationRule(rules operation, token *token_ptr) {
    switch (operation) {
    case E_PLUS_E:
        printf("ADDS\n");
        break;
    case E_MINUS_E:
        printf("SUBS\n");
        break;
    case E_MULTIPLE_E:
        printf("MULS\n");
        break;
    case E_DIVIDE_E:
        printf("DIVS\n");
        break;
    case E_IDIV_E:
        printf("IDIVS\n");
        break;
    case E_CONCAT_E:
        printf("POPS LF@&2\n");
        printf("POPS LF@&1\n");
        printf("CONCAT LF@tempstring LF@&1 LF@&2\n");
        printf("PUSHS LF@tempstring\n");
        break;
    case E_LT_E:
        printf("LTS\n");
        break;
    case E_GT_E:
        printf("GTS\n");
        break;
    case E_EQ_E:
        printf("EQS\n");
        break;
    case E_NEQ_E:
        printf("EQS\n");
        printf("NOTS\n");
        break;
    case E_LEQ_E:
        printf("PUSHS LF@&1\n");
        printf("PUSHS LF@&2\n");
        printf("PUSHS LF@&1\n");
        printf("PUSHS LF@&2\n");
        printf("EQS\n");
        printf("POPS LF@tempbool\n");
        printf("LTS\n");
        printf("PUSHS LF@tempbool\n");
        printf("ORS\n");
        printf("PUSHS bool@true\n");
        printf("EQS\n");
        break;
    case E_GEQ_E:
        printf("PUSHS LF@&1\n");
        printf("PUSHS LF@&2\n");
        printf("PUSHS LF@&1\n");
        printf("PUSHS LF@&2\n");
        printf("EQS\n");
        printf("POPS LF@tempbool\n");
        printf("GTS\n");
        printf("PUSHS LF@tempbool\n");
        printf("ORS\n");
        printf("PUSHS bool@true\n");
        printf("EQS\n");
        break;
    case ID:

        if (token_ptr->ID == TOKEN_VARIABLE) {
            printf("PUSHS LF@");
            printf("%s", token_ptr->VAL.string);
            printf("\n");
        }
        else if (token_ptr->ID == TOKEN_INTEGER || token_ptr->ID == TOKEN_FLOAT || token_ptr->ID == TOKEN_STRING) {
            printf("PUSHS ");
            generateTerm(token_ptr);
            printf("\n");
        }
        else if (token_ptr->ID == TOKEN_KW_NIL) {
            printf("PUSHS nil@nil\n");
        }
        break;
    default:
    case NONE:
        break;
    }

}

bool implicit_conversion(data_type type, data_type converted_type, char *var1) {

    if (converted_type == FLOAT && type == INT) {
        printf("INT2FLOAT TF@%s TF@%s\n", var1, var1);
    }
    else if (converted_type == INT && type == FLOAT) {
        printf("FLOAT2INT TF@%s TF@%s\n", var1, var1);
    }
    else if (converted_type == NULL_TYPE && type == STRING) {
        printf("MOVE TF@%s string@\n",var1);
    }
    else if (converted_type == NULL_TYPE && type == INT) {
        printf("MOVE TF@%s int@0\n", var1);
    }
    else if (converted_type == NULL_TYPE && type == FLOAT) {
        printf("MOVE TF@%s float@0.0\n", var1);
    }
    else {
        return false;
    }

    return true;
}

void builtin_write(){
    printf("LABEL $$write\n");
    printf("PUSHFRAME\n");

    for (int i = 0; i < argument_counter; i++)
    {
        printf("DEFVAR LF@param%d\n", i);
        printf("MOVE LF@param%d LF@%%d\n", i);
        printf("WRITE LF@param%d\n", i);
    }

    printf("POPFRAME\n");
    printf("RETURN\n");
}