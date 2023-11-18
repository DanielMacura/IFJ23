/**
 * Project: IFJ23 Compiler
 *
 * @file analysis.c
 * @brief Implementation of syntax analysis
 *
 * @authors xmacur09
 */

#include "analyser.h"

extern error ERROR;

char* nonterminals[24] = {"body","optional_enter","parameters","type","nested_body","expression","return","end_of_command","function_call","definition","assignment","discard_parameter_name","parameters_prime","c_type","postfix","end_of_command_prime","arguments","definition_prime","assignment_prime","arguments_var","literal","arguments_lit","definition_prime_prime","arguments_prime"};
int runSyntax(lexer_T  *lexer, DLL *dll){
    Stack* stack = createStack(100);
    push(stack, STARTSTATE);

    token *token_ptr;
    next_token();

    do
    {
        printf("--------------------\n");
        printStack(stack);

        int popped = pop(stack);

        if(ISACT(popped)){                          // the symbol at top of stack represents an action
            printf("Action: %d\n", popped);
        }
        else if (ISNONTERM(popped)){                // the symbol at top of stack represents a nonterminal
            printf("Nonterminal: %d\n", popped);
            printf("Token: %d\n", token_ptr->ID);
            printf("Popped: %d   %d\n", popped, popped-MINNONTERM);
            int what_to_push = table[popped-MINNONTERM][token_ptr->ID];
            printf("Push: %d\n", what_to_push);
            if (what_to_push == -1)
            { // syntax error
                printf("Syntax error: %d\n", popped);
                return SYNTAX_ERR;
            }
            else if (what_to_push == 0){
                printf("Epsilon\n");

            }
            else{                                   // push the production to the stack
                int *production = productions[what_to_push];
                
                int i = 0;
                while (production[i] != 0)
                {
                    printf("Pushing: %d\n", production[i]);
                    push(stack, production[i]);
                    i++;
                }
            }
        }
        else if (ISTERM(popped)){                   // the symbol at top of stack represents a terminal 
            printf("Terminal: %d - %s\n", popped, token_names[popped]);
            if (popped == (int)token_ptr->ID){               // the symbol at top of stack matches the current token
                next_token();
                printf("Match: %d\n", popped);
            }
            else{                                   // syntax error
                printf("Error popped, got: %d-%s / %d-%s\n", popped, token_names[popped], token_ptr->ID, token_names[token_ptr->ID]);
                return SYNTAX_ERR;
            }
        }
        else{
            printf("Unknown error: %d\n", popped);          // unknown error
            return SYNTAX_ERR;

        }
    } while (stack->top != -1);     // while stack is not empty

    return SUCCESS;
}

