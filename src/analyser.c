#include "analyser.h"

char* nonterminals[20] = {"body","parameters","type","nested_body","return","end_of_command","function_call","definition","assignment","discard_parameter_name","parameters_prime","c_type","postfix","end_fo_command_prime","arguments","definition_prime","assignment_prime","arguments_prime","definition_prime_prime","arguments_prime_prime"};

int runSyntax(lexer_T  *lexer){
    Stack* stack = createStack(100);
    push(stack, STARTSTATE);
    token *Token = malloc(sizeof(token));


    int return_code = lexer_next_token(lexer, Token);

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
            printf("Token: %d\n", Token->ID);
            printf("Popped: %d   %d\n", popped, popped-MINNONTERM);
            int what_to_push = table[popped-MINNONTERM][Token->ID];
            printf("Push: %d\n", what_to_push);
            if (what_to_push == -1)
            { // syntax error
                printf("Error: %d\n", popped);
                return 1;
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
            if (popped == Token->ID){               // the symbol at top of stack matches the current token
                return_code = lexer_next_token(lexer, Token);
                printf("Match: %d\n", popped);
            }
            else{                                   // syntax error
                printf("Error popped, got: %d-%s / %d-%s\n", popped, token_names[popped], Token->ID, token_names[Token->ID]);
                return 1;
            }
        }
        else{
            printf("Error: %d\n", popped);          // unknown error
            return 1;

        }
    } while (stack->top != -1);     // while stack is not empty

    return 0;
}

