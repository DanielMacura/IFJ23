/**
 * @file analyzer.c
 * @author Daniel Mačura (xmacur09@vutbr.cz)
 * @brief Implementation of top-down syntax analyzer
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "analyzer.h"

extern error_code ERROR;
int argument_counter = 0;
char* function_name;

char* nonterminals[24] = {"body","optional_enter","parameters","type","nested_body","expression","return","end_of_command","function_call","definition","assignment","discard_parameter_name","parameters_prime","c_type","postfix","end_of_command_prime","arguments","definition_prime","assignment_prime","arguments_var","literal","arguments_lit","definition_prime_prime","arguments_prime"};

int runSyntax(lexer_T  *lexer, DLL *dll){
    Stack* stack = createStack(100); 
    push(stack, STARTSTATE);
    DLLElementPtr token_ptr_before;
    data_type final_type = UNDEFINED;

    token *token_ptr;
    next_token();

    beginGenerator();

    do
    {
        verbose("--------------------\n");
        printStack(stack);

        int popped = pop(stack);

        if(ISACT(popped)){                          // the symbol at top of stack represents an action
            verbose("Action: %d\n", popped);
            int errorno = actions(popped, dll, token_ptr_before, &final_type);
            if(errorno != SUCCESS){
                fprintf(stderr, "Error: %d\n", errorno);
                return errorno;
            }
        }
        else if (ISNONTERM(popped)){                // the symbol at top of stack represents a nonterminal
            token_ptr_before = dll->activeElement;
            if(popped == STARTSTATE+5){             // We got an expression
                verbose("Expression\n");
                return_token();
                int result = parse_expression(lexer, dll, &final_type, false);
                if (result == false){
                    return ERROR;
                }
                next_token();
                verbose("Expression end\n");
                continue;
            }
            verbose("Nonterminal: %d - %s\n", popped, nonterminals[popped-MINNONTERM]);
            verbose("Token: %d\n", token_ptr->ID);
            verbose("Popped: %d   %d\n", popped, popped-MINNONTERM);
            int what_to_push = table[popped-MINNONTERM][token_ptr->ID];
            verbose("Push: %d\n", what_to_push);
            if (what_to_push == -1)
            { // syntax error
                printf("Syntax error: %d\n", popped);
                set_error(SYNTAX_ERR);
                return ERROR;
            }
            else if (what_to_push == 0){
                verbose("Epsilon\n");

            }
            else{                                   // push the production to the stack
                int *production = productions[what_to_push];
                
                int i = 0;
                while (production[i] != 0)
                {
                    verbose("Pushing: %d\n", production[i]);
                    push(stack, production[i]);
                    i++;
                }
            }
        }
        else if (ISTERM(popped)){                   // the symbol at top of stack represents a terminal 
            verbose("Terminal: %d - %s\n", popped, token_names[popped]);
            if (popped == (int)token_ptr->ID){               // the symbol at top of stack matches the current token
                next_token();
                verbose("Match: %d\n", popped);
            }
            else{                                   // syntax error
                printf("Error popped, got: %d-%s / %d-%s\n", popped, token_names[popped], token_ptr->ID, token_names[token_ptr->ID]);
                set_error(SYNTAX_ERR);
                return SYNTAX_ERR;
            }
        }
        else{
            printf("Unknown error: %d\n", popped);          // unknown error
            set_error(SYNTAX_ERR);
            return SYNTAX_ERR;

        }
    } while (stack->top != -1);     // while stack is not empty

    endMain();
    endGenerator();
    return SUCCESS;
}

