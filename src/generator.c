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
extern Stack *recursion_stack;
extern int ERROR;
char *defvar_string;

void beginGenerator(){
    char * defvar_string = chararray_init(0);
    generatePrint(".IFJcode23\n");

    generatePrint("JUMP $$definitions\n");
    
    //generateBuiltin();

    beginMain();
}

void generateBuiltin(){

    // Coalesce
    generatePrint("LABEL $$coalesce\n");
    generatePrint("POPS LF@&1\n");
    generatePrint("POPS LF@&2\n");
    generatePrint("JUMPIFEQS $$coalesce_end\n");
    generatePrint("PUSHS LF@&1\n");
    generatePrint("RETURN\n");
    generatePrint("LABEL $$coalesce_end\n");
    generatePrint("PUTS LF@&2\n");
    generatePrint("RETURN\n");

}

void endGenerator(){
    generatePrint("LABEL $$end\n");
    generatePrint("EXIT int@0\n");
}

void beginMain(){
    generatePrint("LABEL $$main\n");

    create_frame();
    push_frame();

}

void endMain(){
    generatePrint("JUMP $$main_end\n");
    generatePrint("LABEL $$definitions\n");
    if(defvar_string != NULL){
        generatePrint("%s", defvar_string);
    }
    generatePrint("JUMP $$main\n");

    generatePrint("LABEL $$main_end\n");

    pop_frame();
}

void defineVariable(char *name){
    char buffer[1024];  
    sprintf(buffer, "DEFVAR GF@%s_%d_%d\n", name, peek(recursion_stack), peek(block_stack));
    chararray_append_string(&defvar_string, buffer);

    SymbolData *symbol =get_symbol_from_frame(LOCAL_FRAME, name, CREATE);

    if (symbol == NULL){
        set_error(UNDEFINED_VAR_ERR);
        return;
    }


}

void defineFunction(char *name){
    generatePrint("LABEL $%s\n", name);
    get_symbol_from_frame(GLOBAL_FRAME, name, CREATE);
}

void popToVariable(char *name) {
    char buffer[1024];
    get_block_id(name, buffer);
    generatePrint("POPS GF@%s_%s\n", name, buffer);
}

void generateTerm(token *token_ptr) {

    if (token_ptr->ID == TOKEN_INTEGER) {
        generatePrint("int@%s", token_ptr->VAL.string);
    }
    else if (token_ptr->ID == TOKEN_FLOAT) {
        generatePrint("float@%a", atof(token_ptr->VAL.string));
    }
    else if (token_ptr->ID == TOKEN_STRING) {
        generatePrint("string@%s", token_ptr->VAL.string);
    }
    else if (token_ptr->ID == TOKEN_VARIABLE) {
        char buffer[1024];
        get_block_id(token_ptr->VAL.string, buffer);
        generatePrint("GF@%s_%s", token_ptr->VAL.string, buffer);
    }
}

void operationRule(rules operation, token *token_ptr) {
    switch (operation) {
    case E_PLUS_E:
        generatePrint("ADDS\n");
        break;
    case E_MINUS_E:
        generatePrint("SUBS\n");
        break;
    case E_MULTIPLE_E:
        generatePrint("MULS\n");
        break;
    case E_DIVIDE_E:
        generatePrint("DIVS\n");
        break;
    case E_IDIV_E:
        generatePrint("IDIVS\n");
        break;
    case E_CONCAT_E:
        generatePrint("POPS LF@&2\n");
        generatePrint("POPS LF@&1\n");
        generatePrint("CONCAT LF@tempstring LF@&1 LF@&2\n");
        generatePrint("PUSHS LF@tempstring\n");
        break;
    case E_LT_E:
        generatePrint("LTS\n");
        break;
    case E_GT_E:
        generatePrint("GTS\n");
        break;
    case E_EQ_E:
        generatePrint("EQS\n");
        break;
    case E_NEQ_E:
        generatePrint("EQS\n");
        generatePrint("NOTS\n");
        break;
    case E_LEQ_E:
        generatePrint("PUSHS LF@&1\n");
        generatePrint("PUSHS LF@&2\n");
        generatePrint("PUSHS LF@&1\n");
        generatePrint("PUSHS LF@&2\n");
        generatePrint("EQS\n");
        generatePrint("POPS LF@tempbool\n");
        generatePrint("LTS\n");
        generatePrint("PUSHS LF@tempbool\n");
        generatePrint("ORS\n");
        generatePrint("PUSHS bool@true\n");
        generatePrint("EQS\n");
        break;
    case E_GEQ_E:
        generatePrint("PUSHS LF@&1\n");
        generatePrint("PUSHS LF@&2\n");
        generatePrint("PUSHS LF@&1\n");
        generatePrint("PUSHS LF@&2\n");
        generatePrint("EQS\n");
        generatePrint("POPS LF@tempbool\n");
        generatePrint("GTS\n");
        generatePrint("PUSHS LF@tempbool\n");
        generatePrint("ORS\n");
        generatePrint("PUSHS bool@true\n");
        generatePrint("EQS\n");
        break;
    case E_COALESCE_E:
        generatePrint("PUSHS LF@&1\n");
        generatePrint("PUSHS nil@nil\n");
        generatePrint("EQS\n");
        generatePrint("PUSHS LF@&2\n");
        generatePrint("PUSHS LF@&1\n");
        generatePrint("JUMP $$coalesce\n");
        break;
        
    case ID:
        if (token_ptr->ID == TOKEN_VARIABLE) {
            char buffer[1024];
            get_block_id(token_ptr->VAL.string, buffer);
            generatePrint("PUSHS GF@%s_%s\n",token_ptr->VAL.string, buffer);
        }
        else if (token_ptr->ID == TOKEN_INTEGER || token_ptr->ID == TOKEN_FLOAT || token_ptr->ID == TOKEN_STRING) {
            generatePrint("PUSHS ");
            generateTerm(token_ptr);
            generatePrint("\n");
        }
        else if (token_ptr->ID == TOKEN_KW_NIL) {
            generatePrint("PUSHS nil@nil\n");
        }
        break;
    default:
    case NONE:
        break;
    }

}

bool implicit_conversion(data_type type, data_type converted_type, char *var1) {

    if (converted_type == FLOAT && type == INT) {
        generatePrint("INT2FLOAT TF@%s TF@%s\n", var1, var1);
    }
    else if (converted_type == INT && type == FLOAT) {
        generatePrint("FLOAT2INT TF@%s TF@%s\n", var1, var1);
    }
    else if (converted_type == NULL_TYPE && type == STRING) {
        generatePrint("MOVE TF@%s string@\n",var1);
    }
    else if (converted_type == NULL_TYPE && type == INT) {
        generatePrint("MOVE TF@%s int@0\n", var1);
    }
    else if (converted_type == NULL_TYPE && type == FLOAT) {
        generatePrint("MOVE TF@%s float@0.0\n", var1);
    }
    else {
        return false;
    }

    return true;
}
