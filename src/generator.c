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
extern Stack *block_stack;

void beginGenerator(){
    printf(".IFJcode23\n");

    printf("JUMP $$main\n");
    
    //generateBuiltin();

    beginMain();
}

void generateBuiltin(){

    // Coalesce
    printf("LABEL $$coalesce\n");
    printf("POPS LF@&1\n");
    printf("POPS LF@&2\n");
    printf("JUMPIFEQS $$coalesce_end\n");
    printf("PUSHS LF@&1\n");
    printf("RETURN\n");
    printf("LABEL $$coalesce_end\n");
    printf("PUTS LF@&2\n");
    printf("RETURN\n");

}

void endGenerator(){
    printf("LABEL $$end\n");
    printf("EXIT int@0\n");
}

void beginMain(){
    printf("LABEL $$main\n");

    create_frame();
    push_frame();

}

void endMain(){
    printf("LABEL $$main_end\n");
    pop_frame();
}

void defineVariable(char *name){
    printf("DEFVAR GF@%s_%d\n", name, peek(block_stack));
}

void popToVariable(char *name) {
    printf("POPS GF@%s_%d\n", name, get_block_id(name));
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
        printf("GF@%s_%d", token_ptr->VAL.string, get_block_id(token_ptr->VAL.string));
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
    case E_COALESCE_E:
        printf("PUSHS LF@&1\n");
        printf("PUSHS nil@nil\n");
        printf("EQS\n");
        printf("PUSHS LF@&2\n");
        printf("PUSHS LF@&1\n");
        printf("JUMP $$coalesce\n");
        break;
        
    case ID:
        if (token_ptr->ID == TOKEN_VARIABLE) {
            printf("PUSHS GF@%s_%d\n",token_ptr->VAL.string, get_block_id(token_ptr->VAL.string));
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
