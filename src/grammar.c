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

extern bst_node_t *global_frame;
extern int argument_counter;
extern error_code ERROR;
extern char *function_name;
extern Stack *block_stack;
extern Stack *recursion_stack;
extern int block_counter;
char defined_function_name[1024];

char* nonterminals[24] = {"body","optional_enter","parameters","type","nested_body","expression","return","end_of_command","function_call","definition","assignment","discard_parameter_name","parameters_prime","c_type","postfix","end_of_command_prime","arguments","definition_prime","assignment_prime","arguments_var","literal","arguments_lit","definition_prime_prime","arguments_prime"};


/**
 * @brief Define the right hand side of each production, listed back to front.
 * 
 */
int Prod0[] = {0};                 // ε
int Prod1[] = {256,257,528,7,260,257,6,527,259,5,4,258,3,257,525,2,1,0};                 // TOKEN_KW_FUNC TOKEN_IDENTIFIER 525 optional_enter TOKEN_LBRACKET parameters TOKEN_RBRACKET TOKEN_ARROW type 527 TOKEN_LCURLYBRACKET optional_enter nested_body TOKEN_RCURLYBRACKET 528 optional_enter body
int Prod2[] = {256,257,521,7,260,257,520,6,257,9,257,7,260,519,257,6,257,261,8,0};                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET optional_enter 519 nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE optional_enter TOKEN_LCURLYBRACKET 520 optional_enter nested_body TOKEN_RCURLYBRACKET 521 optional_enter body
int Prod3[] = {256,257,524,7,260,523,257,6,257,261,522,10,0};                 // TOKEN_KW_WHILE 522 expression optional_enter TOKEN_LCURLYBRACKET optional_enter 523 nested_body TOKEN_RCURLYBRACKET 524 optional_enter body
int Prod4[] = {256,263,262,11,0};                 // TOKEN_KW_RETURN return end_of_command body
int Prod5[] = {256,263,264,514,0};                 // 514 function_call end_of_command body
int Prod6[] = {256,263,513,265,0};                 // definition 513 end_of_command body
int Prod7[] = {256,263,513,266,0};                 // assignment 513 end_of_command body
int Prod8[] = {0};                 // ε
int Prod9[] = {260,257,521,7,260,257,520,6,257,9,257,7,260,519,257,6,257,261,8,0};                 // TOKEN_KW_IF expression optional_enter TOKEN_LCURLYBRACKET optional_enter 519 nested_body TOKEN_RCURLYBRACKET optional_enter TOKEN_KW_ELSE optional_enter TOKEN_LCURLYBRACKET 520 optional_enter nested_body TOKEN_RCURLYBRACKET 521 optional_enter nested_body
int Prod10[] = {260,257,524,7,260,523,257,6,257,261,522,10,0};                 // TOKEN_KW_WHILE 522 expression optional_enter 523 TOKEN_LCURLYBRACKET optional_enter 523 nested_body TOKEN_RCURLYBRACKET 524 optional_enter nested_body
int Prod11[] = {260,263,262,11,0};                 // TOKEN_KW_RETURN return end_of_command nested_body
int Prod12[] = {260,263, 264,514,0};                 // 514 function_call end_of_command nested_body
int Prod13[] = {260,263,513,265,0};                 // definition 513 end_of_command nested_body
int Prod14[] = {260,263,513,266,0};                 // assignment 513 end_of_command nested_body
int Prod15[] = {0};                 // ε
int Prod16[] = {257,12,0};                 // TOKEN_EOL optional_enter
int Prod17[] = {273,14,512,13,0};                 // TOKEN_KW_VAR 512 TOKEN_VARIABLE definition_prime
int Prod18[] = {273,14,512,15,0};                 // TOKEN_KW_LET 512 TOKEN_VARIABLE definition_prime
int Prod19[] = {278,259,16,0};                 // TOKEN_COLON type definition_prime_prime
int Prod20[] = {274,17,0};                 // TOKEN_EQUALS 531 assignment_prime
int Prod21[] = {0};                 // ε
int Prod22[] = {274,17,0};                 // TOKEN_EQUALS 531 assignment_prime
int Prod23[] = {274,17,14,0};                 // TOKEN_VARIABLE 531 TOKEN_EQUALS  assignment_prime
int Prod24[] = {261,0};                 // expression
int Prod25[] = {518, 264, 514,0};                 // 531 514 function_call 518       <-- from assignment_prime
int Prod26[] = {516, 4,515,272,517,3,2,0};                 // TOKEN_IDENTIFIER TOKEN_LBRACKET reset_arg_counter 517 arguments 515 TOKEN_RBRACKET 516
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
int Prod40[] = {268,526,259,16,14,267,0};                 // discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type 526 parameters_prime
int Prod41[] = {0};                 // ε
int Prod42[] = {268,526,259,16,14,267,25,0};                 // TOKEN_COMMA discard_parameter_name TOKEN_VARIABLE TOKEN_COLON type 526 parameters_prime
int Prod43[] = {14,0};                 // TOKEN_VARIABLE
int Prod44[] = {26,0};                 // TOKEN_UNDERSCORE
int Prod45[] = {0};                 // ε
int Prod46[] = {275,14,0};                 // TOKEN_VARIABLE arguments_var
int Prod47[] = {277,276,0};                 // literal arguments_lit
int Prod48[] = {275,14,0};                 // TOKEN_VARIABLE arguments_var
int Prod49[] = {277,276,0};                 // literal arguments_lit
int Prod50[] = {0};                 // ε
int Prod51[] = {279,25,515,0};                 // 515 TOKEN_COMMA arguments_prime
int Prod52[] = {272,276,16,0};                 // TOKEN_COLON literal arguments
int Prod53[] = {0};                 // ε
int Prod54[] = {279,25,515,0};                 // 515 TOKEN_COMMA arguments_prime
int Prod55[] = {529,0};                 // 529, ε
int Prod56[] = {530,261,0};                 // expression
int Prod57[] = {264,514,0};                 //514 function_call
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
int Prod81[] = {256, 12, 0};                 // EOL body
int Prod82[] = {261,12,0};                 // EOL expression
int Prod83[] = {260, 12, 0};                 // EOL nested_body

int *productions[] = {
    Prod0, Prod1, Prod2, Prod3, Prod4, Prod5, Prod6, Prod7, Prod8, Prod9,
    Prod10, Prod11, Prod12, Prod13, Prod14, Prod15, Prod16, Prod17, Prod18, Prod19,
    Prod20, Prod21, Prod22, Prod23, Prod24, Prod25, Prod26, Prod27, Prod28, Prod29,
    Prod30, Prod31, Prod32, Prod33, Prod34, Prod35, Prod36, Prod37, Prod38, Prod39,
    Prod40, Prod41, Prod42, Prod43, Prod44, Prod45, Prod46, Prod47, Prod48, Prod49,
    Prod50, Prod51, Prod52, Prod53, Prod54, Prod55, Prod56, Prod57, Prod58, Prod59,
    Prod60, Prod61, Prod62, Prod63, Prod64, Prod65, Prod66, Prod67, Prod68, Prod69,
    Prod70, Prod71, Prod72, Prod73, Prod74, Prod75, Prod76, Prod77, Prod78, Prod79,
    Prod80, Prod81, Prod82, Prod83
};

void actions(int action_num, DLL *dll, DLLElementPtr ptr_before_expression, data_type *final_type){
    DLLElementPtr activeElement = dll->activeElement; //remember active element
    SymbolData *function;
    SymbolData *variable;
    int should_push_value_to_variable = 0;
    char buffer[1024];


    switch (action_num)
    {
        /**
         * @brief Define a variable with a given name.
         * 
         */
        case 512:
            if (dll->activeElement->data.ID == TOKEN_VARIABLE)
            {
                defineVariable(dll->activeElement->data.VAL.string);
            }
            else{
                set_error(SYNTAX_ERR);
            }
        
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


            // we found a eqauls token, which means we are assigning a value to a variable, e.i. it is defined
            if (should_push_value_to_variable){
                frame_type parent_frame;
                SymbolData *variable = get_symbol(dll->activeElement->data.VAL.string, FIND_UNINITIALIZED, &parent_frame);
                //we get the value from the stack and push it to the variable
                //we set the variable type
                if (variable == NULL){
                    
                    set_error(UNDEFINED_VAR_ERR);
                    return;
                }
                if(variable->type == VAR_DATA){

                    variable->data.varData.is_initialized = 1;
                    variable->data.varData.is_defined = 1;
                    
                    variable->data.varData.type = *final_type;
                    popToVariable(dll->activeElement->data.VAL.string);
                }
                else{
                    set_error(SYNTAX_ERR);
                    return;
                }

            }
            dll->activeElement = activeElement;    //return to active element
            break;


        /**
         * @brief When a function is called, get the identifier, create a new temporary frame, set a jump to the function,
         *        and create a label called jump_to_function, which will be used when arguments are parsed.
         * 
         */
        case 514:
            function_name = dll->activeElement->data.VAL.string;

            create_frame();
            generatePrint("CREATEFRAME\n");
            generatePrint("DEFVAR TF@%%retval\n");             
            break;


        /**
         * @brief Called at each argument, pushes the argument to the stack.
         * 
         */
        case 515:
            // find which argument we are parsing, count them

            DLL_move_active_left(dll);  //was called on comma or right bracket, so we need to move left
            if(dll->activeElement->data.ID == TOKEN_LBRACKET){
                DLL_move_active_right(dll); //move right to the first argument
                break;
            }
            generatePrint("DEFVAR TF@%%arg%d\n", argument_counter);
            switch (dll->activeElement->data.ID)
            {
                case TOKEN_INTEGER:
                    generatePrint("MOVE TF@%%arg%d int@%s\n", argument_counter, dll->activeElement->data.VAL.string);
                    break;
                case TOKEN_FLOAT:
                    generatePrint("MOVE TF@%%arg%d float@%a\n", argument_counter,  strtod(dll->activeElement->data.VAL.string, NULL));
                    break;
                case TOKEN_STRING:
                    generatePrint("MOVE TF@%%arg%d string@%s\n", argument_counter, dll->activeElement->data.VAL.string);
                    break;
                case TOKEN_VARIABLE:
                    get_block_id(dll->activeElement->data.VAL.string, buffer);
                    generatePrint("MOVE TF@%%arg%d GF@%s_%s\n", argument_counter, dll->activeElement->data.VAL.string, buffer);
                    break;
                case TOKEN_KW_NIL:
                    generatePrint("MOVE TF@%%arg%d nil@nil\n", argument_counter);
                    break;
                default:
                    set_error(SYNTAX_ERR);
                    break;
            }
            DLL_move_active_right(dll); //move right to the comma or right bracket


            if (strcmp(function_name, "write") == 0)
            {
                generatePrint("WRITE TF@%%arg%d\n", argument_counter);
            }
            else if(strcmp(function_name, "readInt") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
            }
            else if(strcmp(function_name, "readString") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
            }
            else if(strcmp(function_name, "readDouble") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
            }
            else if (strcmp(function_name, "Int2Double")==0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("PUSHS TF@%%arg%d\n", argument_counter);
                generatePrint("INT2FLOATS\n");
                generatePrint("POPS TF@%%retval\n");
            }
            else if (strcmp(function_name, "Double2Int")==0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("PUSHS TF@%%arg%d\n", argument_counter);
                generatePrint("FLOAT2INTS\n");
                generatePrint("POPS TF@%%retval\n");
            }
            else if(strcmp(function_name, "length") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("STRLEN TF@%%retval TF@%%arg%d\n", argument_counter);
            }
            else if(strcmp(function_name, "ord") == 0){
                generatePrint("STRI2INT TF@%%retval TF@%%arg%d int@%d\n", argument_counter, 0);
            }
            else if(strcmp(function_name, "chr") == 0){
                generatePrint("INT2CHAR TF@%%retval TF@%%arg%d\n", argument_counter);
            }


            argument_counter++;
            break;


        /**
         * @brief After all arguments are parsed, we call the function handle return value.
         * 
         */
        case 516:
            if (strcmp(function_name, "write") == 0)
            {
                break;
            }
            else if(strcmp(function_name, "readInt") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("READ TF@%%retval int\n");
            }
            else if(strcmp(function_name, "readString") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("READ TF@%%retval string\n");
            }
            else if(strcmp(function_name, "readDouble") == 0){
                if (argument_counter != 0)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                generatePrint("READ TF@%%retval float\n");
            }
            //single argument functions handled in previous action
            else if (strcmp(function_name, "Int2Double")==0 || strcmp(function_name, "Double2Int")==0 || strcmp(function_name, "length") == 0 || strcmp(function_name, "ord") == 0 || strcmp(function_name, "chr") == 0){
                break;
            }
            else if(strcmp(function_name, "substring")==0){
                if (argument_counter != 3)
                {
                    set_error(PARAMETERS_ERR);
                    break;
                }
                //arg0 = string
                //arg1 = index
                //arg2 = end index
                generatePrint("PUSHS TF@%%arg%d\n", 0);
                generatePrint("PUSHS int@0\n");
                generatePrint("LTS\n");
            }
            else{
                generatePrint("CALL $%s\n", function_name);

            }
            break;
            

        /**
         * @brief Reset argument counter.
         * 
         */
        case 517:
            argument_counter = 0;
            break;


        /**
         * @brief Push the return value of a function to the stack. Used to assign the return value to a variable.
         * 
         */
        case 518:
            generatePrint("PUSHS TF@%%retval\n");
            break;
        break;


        /**
         * @brief First part of a if statement, already has bool value on the stack.
         *        We create the jumpifEQ to jump to the else label, which is named with the label counter.
         *        We push the label counter to the stack, so we can later pop it and use it for the else label.
         *        This allows us to have nested if statements.
         * 
         */
        case 519:
            generatePrint("PUSHS bool@true\n");
            create_frame();
            push_frame();
            generatePrint("JUMPIFNEQS $$else%d\n", peek(block_stack));

            break;


        /**
         * @brief The second part of the if statement, the ELSE statement.
         *        
         */
        case 520:

            generatePrint("JUMP $$endif%d\n", peek(block_stack)); // ensures we jump over else block if we didnt jump to it from the if statemnt
            generatePrint("LABEL $$else%d\n", peek(block_stack));

            break;


        /**
         * @brief End of the if statement, we pop the label counter from the stack and create the endif label.
         * 
         */
        case 521:
            generatePrint("LABEL $$endif%d\n", peek(block_stack));
            pop_frame();
            break;


        /**
         * @brief First part of a while statement, we create the label for the top while loop to check the condition.
         *        If the condition is false, we jump to the end of the while loop.
         * 
         *        MUST be called before the expression is parsed
         */
        case 522:
            generatePrint("LABEL $$while%d\n", block_counter);
            create_frame();
            push_frame();
            break;


        /**
         * @brief Second part of a while statement, after the expression is parsed.
         * 
         */
        case 523:
            generatePrint("PUSHS bool@true\n");
            generatePrint("JUMPIFNEQS $$endwhile%d\n", peek(block_stack));
            break;


        /**
         * @brief Third part of a while statement, called at the end of the innerloop.
         * 
         */
        case 524:
            generatePrint("JUMP $$while%d\n", peek(block_stack));
            generatePrint("LABEL $$endwhile%d\n", peek(block_stack));
            pop_frame();
            break;

        /**
         * @brief This action is called when a function is defined. We create a label for the function.
         * 
         */
        case 525:
            DLL_move_active_left(dll); // move to the identifier
            create_frame();
            push_frame();
            generatePrint("JUMP $$end_%s\n", dll->activeElement->data.VAL.string);
            defineFunction(dll->activeElement->data.VAL.string);

            strcpy(defined_function_name, dll->activeElement->data.VAL.string);
            dll->activeElement = activeElement;    //return to active element
            
            break;

        /**
         * @brief This action is called afte every parameter in the function definition.
         * 
         */
        case 526:
            function = get_symbol_from_frame(GLOBAL_FRAME, defined_function_name, FIND);


            if (function){
                DLL_move_active_left(dll); // was called on type, so we need to move left
                
                data_type type;
                if (dll->activeElement->data.ID == TOKEN_KW_INT)
                {
                    type = INT;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_DOUBLE)
                {
                    type = FLOAT;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_STRING)
                {
                    type = STRING;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_NIL)
                {
                    type = NULL_TYPE;
                }
                else
                {
                    set_error(SYNTAX_ERR);
                    return;
                }
                
                DLL_move_active_left(dll); // move past the colon
                DLL_move_active_left(dll); // move to the name

                function->data.funcData.parameters = realloc(function->data.funcData.parameters, (function->data.funcData.num_of_params + 1) * sizeof(parameter));

                function->data.funcData.parameters[function->data.funcData.num_of_params].type = type;
                function->data.funcData.parameters[function->data.funcData.num_of_params].name = dll->activeElement->data.VAL.string;
                generatePrint("MOVE GF@%s_%d_%d TF@%%arg%d\n", dll->activeElement->data.VAL.string, peek(recursion_stack), peek(block_stack), function->data.funcData.num_of_params);
                defineVariable(dll->activeElement->data.VAL.string);

                SymbolData *variable = get_symbol_from_frame(LOCAL_FRAME, dll->activeElement->data.VAL.string, FIND_UNINITIALIZED);
                if (variable == NULL){
                    set_error(UNDEFINED_VAR_ERR);
                    return;
                }

                variable->data.varData.is_initialized = 1;
                variable->data.varData.is_defined = 1;
                variable->data.varData.type = type;

                DLL_move_active_left(dll); // move to the identifier
                if(dll->activeElement->data.ID == TOKEN_VARIABLE){
                    function->data.funcData.parameters[function->data.funcData.num_of_params].identifier = dll->activeElement->data.VAL.string;
                }
                else{
                    function->data.funcData.parameters[function->data.funcData.num_of_params].identifier = NULL;
                }
                function->data.funcData.num_of_params++;


            
            }
            dll->activeElement = activeElement;    //return to active element
            break;

        /**
         * @brief Called after the type of the function is parsed.
         * 
         */
        case 527:
            function = get_symbol_from_frame(GLOBAL_FRAME, defined_function_name, FIND);
            DLL_move_active_left(dll); // move to the type
            if (function)
            {
                data_type type;
                if (dll->activeElement->data.ID == TOKEN_KW_INT)
                {
                    type = INT;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_DOUBLE)
                {
                    type = FLOAT;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_STRING)
                {
                    type = STRING;
                }
                else if (dll->activeElement->data.ID == TOKEN_KW_NIL)
                {
                    type = NULL_TYPE;
                }
                else
                {
                    set_error(SYNTAX_ERR);
                    return;
                }
                function->data.funcData.return_type = type;
            }
            dll->activeElement = activeElement;    //return to active element
            break;


        /**
         * @brief At the end of a function definition, we pop the frame.
         * 
         */
        case 528:
            pop_frame();
            generatePrint("RETURN\n");
            generatePrint("LABEL $$end_%s\n", defined_function_name);

            break;

        /**
         * @brief When an empty return statement is parsed
         * 
         */
        case 529:
            generatePrint("MOVE TF@%%retval nil@nil\n");
            generatePrint("RETURN\n");
            break;
        
        /**
         * @brief When an nonempty return statement is parsed, called after expression
         * 
         */
        case 530:
            generatePrint("POPS TF@%%retval\n");
            generatePrint("RETURN\n");
            break;

        /**
         * @brief Called after a equals token to set the variable as defined.
         * 
         */
        case 531:
            //DLL_move_active_left(dll); // move to the identifier

            while (dll->activeElement->previousElement != NULL)
            {
                if (dll->activeElement->data.ID == TOKEN_VARIABLE)
                {
                    break;
                }

                DLL_move_active_left(dll);
            }



            variable = get_symbol_from_frame(LOCAL_FRAME, dll->activeElement->data.VAL.string, FIND_UNINITIALIZED);
            //we get the value from the stack and push it to the variable
            //we set the variable type
            if (variable == NULL){
                
                set_error(UNDEFINED_VAR_ERR);
                return;
            }

            variable->data.varData.is_initialized = 1;
            variable->data.varData.is_defined = 1;


        
            dll->activeElement = activeElement;    //return to active element
            break;

        default:
            set_error(SYNTAX_ERR);
            return;
            break;
    }
    return;
}
int table[24][43] = {
    { 1,1,5,-1,-1,-1,-1,-1,2,-1,3,4,81,6,7,6,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    { 16,15,15,15,-1,-1,15,15,15,15,15,15,16,15,15,15,-1,-1,-1,-1,-1,-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,27,27,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,12,-1,-1,-1,-1,8,9,-1,10,11,83,13,14,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
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
    {-1,-1,25,24,24,-1,-1,-1,-1,-1,-1,-1,82,-1,24,-1,-1,-1,-1,-1,-1,-1,24,-1,-1,-1,-1,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,-1},
    {-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,-1,-1,-1,-1,58,59,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-1,-1,22,-1,-1,-1,-1,-1,21,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,49,49,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
};
