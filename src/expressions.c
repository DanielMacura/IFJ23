/**
 * Project: IFJ23 Compiler
 * 
 * @file expressions.c
 * @brief Implementation of expression parser
 * 
 * @authors xmacur09
*/

#include "expressions.h"

extern error_code ERROR;


extern int ERRORFROMLEXER;
extern int BODYRECURSIONCOUNT;

size_t COUNTER = 0;

/**
 * @brief Creates new item for stack. Should only be called by macro new_item().
 * 
 * @param token_ptr 
 * @param type 
 * @return expr_item* 
 */
expr_item *expr_item_new(token *token_ptr, expr_item_type type) {
    expr_item *item = malloc(sizeof(*item));
    item->token_ptr = token_ptr;
    item->type = type;
    item->data_type = UNDEFINED;
    item->breakpoint = false;
    item->next_item = NULL;
    return item;
}
/**
 * @brief Creates new stack.
 * 
 * @return expr_stack* 
 */
expr_stack *expr_stack_new() {
    expr_stack *stack = malloc(sizeof(*stack));
    if (!stack)
        return NULL;
    stack->size = 0;
    stack->top_item = NULL;
    return stack;
}
/**
 * @brief Pushes item to top of stack.
 * 
 * @param stack 
 * @param item 
 */
void expr_stack_push(expr_stack *stack, expr_item *item) {
    if (!stack->top_item) { 
        stack->top_item = item;
    }
    else {
        item->next_item = stack->top_item;
        stack->top_item = item;
    }
    stack->size++;
}

/**
 * @brief Pops item from top of stack and returns it.
 * 
 * @param stack 
 * @return expr_item* 
 */
expr_item *expr_stack_pop(expr_stack *stack) {
    if (!stack->top_item) {
        return NULL;
    }
    else {
        expr_item *item = stack->top_item;
        stack->top_item = item->next_item;
        stack->size--;
        return item;
    }
}

/**
 * @brief Frees stack.
 * 
 * @param stack 
 */
void expr_stack_free(expr_stack *stack) {
    expr_item *item = stack->top_item;
    while (item) {
        expr_item *next_item = item->next_item;
        free(item);
        item = next_item;
    }
    free(stack);
}

/**
 * @brief Get the index of token in the precedence table.
 * 
 * @param token_ptr 
 * @return int 
 */
int get_index_token(token *token_ptr) {
    const int dollar = 8;
    if (!token_ptr) { // dollar
        return dollar;
    }
    switch (token_ptr->ID) {
        case TOKEN_LBRACKET:
            return 0;
        case TOKEN_RBRACKET:
            return 1;
        case TOKEN_EXCLAMATIONMARK:
            return 2;
        case TOKEN_MULTIPLICATION:
        case TOKEN_DIVISION:
            return 3;
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return 4;
        case TOKEN_DOUBLE_EQUALS:
        case TOKEN_NOT_EQUALS:
        case TOKEN_LT:
        case TOKEN_GT:
        case TOKEN_LTE:
        case TOKEN_GTE:
            return 5;
        case TOKEN_NIL_COALESCING:
            return 6;
        case TOKEN_VARIABLE:
        case TOKEN_INTEGER:
        case TOKEN_FLOAT:
        case TOKEN_STRING:
        case TOKEN_KW_NIL:
            return 7;

        default:
            return dollar;
    }
}

/**
 * @brief Get the data type if the token. Used for semantic analysis.
 * 
 * @param token_ptr 
 * @return data_type 
 */
data_type get_data_type(token *token_ptr) { // returns data type of token
    switch (token_ptr->ID) {
    case TOKEN_INTEGER:
        return INT;
    case TOKEN_FLOAT:
        return FLOAT;
    case TOKEN_STRING:
        return STRING;
    default:
        return UNDEFINED;
    }
}
/**
 * @brief Get the precedence as defined by the table.
 * 
 * @param token_on_stack 
 * @param token_ptr 
 * @return char - one of '<', '>', '=' or '\0'
 */
char get_precedence(token *token_on_stack, token *token_ptr) { 
    int index[2] = {0, 0};

    index[0] = get_index_token(token_on_stack);
    index[1] = get_index_token(token_ptr);

    if (index[0] == -1 || index[1] == -1) {
        return '\0';
    }

    return precedence_table[index[0]][index[1]];
}

/**
 * @brief Counts number of items in stack before breakpoint.
 * 
 * @param expr_stack 
 * @return int 
 */
int count_breakpoint(expr_stack *expr_stack) {
    int count = 0;
    expr_item *item = expr_stack->top_item;
    while (item) {
        if (!item->breakpoint) {
            count++;
        }
        else {
            item->breakpoint = false;
            break;
        }
        item = item->next_item;
    }
    return count;
}

/*
data_type get_data_type_from_item(expr_item *item_right, expr_item *item_middle, expr_item *item_left, symtables tables) { // returns data type of expression
    if (item_right->type == TERM && item_right->token_ptr->ID != TOKEN_ID_RBRACKET) { // id
        if (item_right->token_ptr->ID == TOKEN_ID_VARIABLE) {
            table_item_data *item = NULL;

            item = hash_table_lookup(tables.local, item_right->token_ptr->VAL.string);

            if (!item) {
                item = hash_table_lookup(tables.global, item_right->token_ptr->VAL.string);
            }

            if (!item) {
                ERROR = UNDEFINED_VAR_ERR;
                return UNDEFINED;
            }
            else {
                if (item->is_var) {
                    return item->f_or_v.variable->type;
                }
                else {
                    ERROR = SEM_OTHER_ERR;
                    return UNDEFINED;
                }
            }
            return INT;
        }
        else if (item_right->token_ptr->ID == TOKEN_ID_INTEGER) {
            return INT;
        }
        else if (item_right->token_ptr->ID == TOKEN_ID_FLOAT) {
            return FLOAT;
        }
        else if (item_right->token_ptr->ID == TOKEN_ID_STRING) {
            return STRING;
        }
    }
    else if (item_middle->type == NONTERM) { // (E)
        return item_middle->data_type;
    }
    else { // E something E
        data_type right = item_right->data_type;
        data_type left = item_left->data_type;

        switch (item_middle->token_ptr->ID) {
        case TOKEN_ID_PLUS:
        case TOKEN_ID_MINUS:
        case TOKEN_ID_MULTIPLICATION:
            if (left == INT) {
                if (right == INT || right == NULL_TYPE) {
                    return INT;
                }
                else if (right == FLOAT) {
                    create_temp_frame();
                    //change type of left to float
                    // pop keeep, pop to var, change var, push var, push keeep
                                        printf("DEFVAR TF@rval\n");
                    printf("DEFVAR TF@lval\n");


                    pop_to_strname("rval");
                    pop_to_strname("lval");
                    implicit_conversion(INT, FLOAT, "lval");
                    push_from_strname("lval");
                    push_from_strname("rval");

                    return FLOAT;
                }
                else {
                    ERROR = EXPR_ERR;
                    return UNDEFINED;
                }
            }
            else if (left == FLOAT) {
                if(right == INT){
                    //change type
                    create_temp_frame();
                    //change type of left to float
                    // pop keeep, pop to var, change var, push var, push keeep


                    printf("DEFVAR TF@rval\n");

                    pop_to_strname("rval");

                    implicit_conversion(INT, FLOAT, "rval");

                    push_from_strname("rval");





                    return FLOAT;
                }
                if (right == FLOAT || right == NULL_TYPE) {
                    return FLOAT;
                }
                else {
                    ERROR = EXPR_ERR;
                    return UNDEFINED;
                }
            }
            else if (left == NULL_TYPE) {
                if (right == INT) {
                    return INT;
                }
                else if (right == FLOAT) {
                    return FLOAT;
                }
                else if (right == NULL_TYPE) {
                    return NULL_TYPE;
                }
                else {
                    ERROR = EXPR_ERR;
                    return UNDEFINED;
                }
            }
            else {
                ERROR = EXPR_ERR;
                return UNDEFINED;
            }
            break;
        case TOKEN_ID_DIVISION:
            if (left == NULL_TYPE && right == NULL_TYPE) {
                ERROR = EXPR_ERR;
                return UNDEFINED;
            } else if ((left == INT || left == FLOAT || left == NULL_TYPE) && (right == INT || right == FLOAT || right == NULL_TYPE)) { 
                return FLOAT;
            }
            else {
                ERROR = EXPR_ERR;
                return UNDEFINED;
            }
            break;
        case TOKEN_ID_CONCAT:
            if ((right == STRING || right == NULL_TYPE) && (left == STRING || left == NULL_TYPE)) {
                return STRING;
            }
            else {
                ERROR = EXPR_ERR;
                return UNDEFINED;
            }
            break;
        case TOKEN_ID_TRIPLE_EQUALS:
        case TOKEN_ID_NOT_EQUALS:
        case TOKEN_ID_LT:
        case TOKEN_ID_GT:
        case TOKEN_ID_LTE:
        case TOKEN_ID_GTE:
            return BOOL_TYPE;
            break;
        default:
            return UNDEFINED;
        }
    }
    return UNDEFINED;
}
*/

/**
 * @brief Applies rule to stack.
 * 
 * @param expr_stack 
 * @param tables 
 * @return true 
 * @return false 
 */
bool apply_rule(expr_stack *expr_stack/*, symtables tables*/) { //FIXME: add back
    int number_of_items = count_breakpoint(expr_stack);

    bool ret_val = false;

    expr_item *item_right = NULL;
    expr_item *item_middle = NULL;
    expr_item *item_left = NULL;

    data_type expression_type = UNDEFINED;

    rules rule;
    //shutup compiler
    (void)rule;
    printf("number of items: %d\n", number_of_items);
    if (number_of_items == 1)
    {
        item_right = expr_stack_pop(expr_stack);
        if (item_right->type == TERM && get_index_token(item_right->token_ptr) == 7) { // E -> id
            rule = ID;
            //expression_type =  get_data_type_from_item(item_right, item_middle, item_left, tables);   //FIXME: add back
            //operation_rule(rule, item_right->token_ptr);  //FIXME: add back code generation
            ret_val = true;
        }
        else {
            printf("return 1\n");
            ret_val = false;
        }
    }
    else if(number_of_items == 2){
        item_right = expr_stack_pop(expr_stack);
        item_middle = expr_stack_pop(expr_stack);

        if (item_right->type == TERM && get_index_token(item_right->token_ptr) == 2 && item_middle->type == NONTERM) { // E -> E!
            rule = E_EXCLAMATION;
            //expression_type =  get_data_type_from_item(item_right, item_middle, item_left, tables);   //FIXME: add back
            //operation_rule(rule, NULL);   //FIXME: add back code generation
            ret_val = true;
        }
        else{
            printf("return 2\n");
            ret_val = false;
        }
    }
    else if (number_of_items == 3) {
        item_right = expr_stack_pop(expr_stack);
        item_middle = expr_stack_pop(expr_stack);
        item_left = expr_stack_pop(expr_stack);

        if (item_left->type == NONTERM && item_middle->type == TERM && item_right->type == NONTERM) {
            if (item_middle->token_ptr->ID == TOKEN_PLUS) { // E -> E + E
                rule =  E_PLUS_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_MINUS) { // E -> E - E
                rule = E_MINUS_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_MULTIPLICATION) { // E -> E * E
                rule = E_MULTIPLE_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_DIVISION) { // E -> E / E
                rule = E_DIVIDE_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_NIL_COALESCING) { // E -> E ?? E
                rule = E_COALESCE_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_DOUBLE_EQUALS) { // E -> E == E
                rule = E_EQ_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_NOT_EQUALS) { // E -> E !== E
                rule = E_NEQ_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_LT) { // E -> E < E
                rule = E_LT_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_GT) { // E -> E > E
                rule = E_GT_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_LTE) { // E -> E <= E
                rule = E_LEQ_E;
                ret_val = true;
            }
            else if (item_middle->token_ptr->ID == TOKEN_GTE) { // E -> E >= E
                rule = E_GEQ_E;
                ret_val = true;
            }
            else {
                printf("return 3\n");
                ret_val = false;
            }
            if (ret_val){
                //expression_type =  get_data_type_from_item(item_right, item_middle, item_left, tables);         //FIXME: add back
                //operation_rule(rule, NULL);   //generate code
            }
        }
        else if ((item_right->type == TERM && get_index_token(item_right->token_ptr) == 2) &&
                 (item_left->type == TERM && get_index_token(item_left->token_ptr) == 1) &&
                 (item_middle->type == NONTERM)) { // E -> (E)
            ret_val = true;
            //expression_type =  get_data_type_from_item(item_right, item_middle, item_left, tables);       //FIXME: add back
        }
        else {
            printf("return 4\n");
            ret_val = false;
        }
    }
    else {
        printf("return 5\n");
        return false;
    }

    if (ret_val) {
        item_right->data_type = expression_type;
        item_right->type = NONTERM;
        item_right->token_ptr = NULL;
        expr_stack_push(expr_stack, item_right);
    }

    if (item_middle) {
        free(item_middle);
        free(item_left);
    }

    return ret_val;
}
/**
 * @brief Returns pointer to top term or dollar on stack.
 * 
 * @param expr_stack 
 * @return expr_item* 
 */
expr_item *get_term_or_dollar(expr_stack *expr_stack) { // 
    expr_item *item = expr_stack->top_item;
    while (item->type != TERM && item->type != DOLLAR)  {
        item = item->next_item;
    }
    return item;
}
/**
 * @brief Parses expression.
 * 
 * @param lexer 
 * @param dll 
 * @param tables 
 * @param final_type 
 * @param exp_brack 
 * @return true - expression is valid
 * @return false - expression is invalid
 */
bool parse_expression(lexer_T *lexer, DLL *dll, /*symtables tables,*/ data_type *final_type, bool exp_brack) { //FIXME: add back
    if (ERROR == LEXICAL_ERR) {
        return false;
    }
    token *token_ptr;
    expr_item *new_item;
    expr_stack *expr_stack = expr_stack_new();
    if (!expr_stack) {
        ERROR = INTERNAL_ERR;
        return false;
    }

    new_item(new_item, NULL, DOLLAR);
    expr_stack_push(expr_stack, new_item);

    next_token_counted();
    if (ERROR) {
        expr_stack_free(expr_stack);
        return_all_tokens();
        return false;
    }

    do { 
        expr_item *stack_term = get_term_or_dollar(expr_stack);
        printf("stack_term: %s\n",stack_term->type==DOLLAR?"dollar" :token_names[stack_term->token_ptr->ID]);
        switch (get_precedence(stack_term->token_ptr, token_ptr)) { // precedence table
            case '=':
                printf("=   %s\n", token_names[token_ptr->ID]);
                new_item(new_item, &dll->activeElement->data, TERM);
                next_token_counted();
                printf("=   next tok %s\n", token_names[token_ptr->ID]);
                expr_stack_push(expr_stack, new_item);
                if (ERROR) {
                    expr_stack_free(expr_stack);
                    return_all_tokens();
                    return false;
                }
                break;
            case '<':
                printf("<   %s\n", token_names[token_ptr->ID]);
                stack_term->breakpoint = true;
                new_item(new_item, &dll->activeElement->data, TERM);
                next_token_counted();
                printf("=   next tok %s\n", token_names[token_ptr->ID]);

                expr_stack_push(expr_stack, new_item);
                if (ERROR) {
                    expr_stack_free(expr_stack);
                    return_all_tokens();
                    return false;
                }
                break;
            case '>':
                printf(">   %s\n", token_names[token_ptr->ID]);
                if (!apply_rule(expr_stack/*, tables*/)) {
                    ERROR = SYNTAX_ERR;
                    printf("BAD expresoizn\n");
                    expr_stack_free(expr_stack);
                    return_all_tokens();
                    return false;
                }
                if (ERROR > 2) { // semantic erro
                    expr_stack_free(expr_stack);
                    return_all_tokens();
                    return false;
                }
                if (expr_stack->top_item->type == NONTERM && expr_stack->top_item->next_item->type == DOLLAR && get_index_token(token_ptr) == 0) { 
                    if (exp_brack) {
                        ERROR = SYNTAX_ERR;
                        expr_stack_free(expr_stack);
                        return_all_tokens();
                        return false;
                    }
                    *final_type = expr_stack->top_item->data_type;
                    expr_stack_free(expr_stack);
                    DLL_move_active_left(dll); 
                    COUNTER = 0;
                    return true; 
                }
                break;
            case 'i':
                printf("i   %s\n", token_names[token_ptr->ID]);

                /*  we got to a state, which may be the end of the expression.
                    we got two terminals which would be an error, so we treat the last
                    terminal as a dollar and try to apply rules.
                    either we get to the end of the expression or we get an error.   */
                expr_item *dollar_term = expr_item_new(NULL, DOLLAR);
                return_token(); //return last token that caused state i
                return_token(); //return one more token and check if it was EOL, if not cosume it. This is because a EOL is needed for end of command nonterminal
                next_token();
                if (token_ptr->ID == TOKEN_EOL) {
                    return_token();
                }

                do
                {
                    switch (get_precedence(stack_term->token_ptr, dollar_term->token_ptr))
                    {
                    case '>':
                        if (!apply_rule(expr_stack/*, tables*/)) {
                            ERROR = SYNTAX_ERR;
                            expr_stack_free(expr_stack);
                            return_all_tokens();
                            return false;
                        }
                        if (expr_stack->top_item->type == NONTERM && expr_stack->top_item->next_item->type == DOLLAR && get_index_token(token_ptr) == 0) { 
                            if (exp_brack) {
                                ERROR = SYNTAX_ERR;
                                expr_stack_free(expr_stack);
                                return_all_tokens();
                                return false;
                            }
                            *final_type = expr_stack->top_item->data_type;
                            expr_stack_free(expr_stack);
                            DLL_move_active_left(dll); 
                            COUNTER = 0;
                            return true; 
                        }
                        break;

                    case '\0' :
                        return false;
                        break;

                    case 'f':
                        *final_type = expr_stack->top_item->data_type;
                        expr_stack_free(expr_stack);
                        COUNTER = 0;
                        return true; 
                        break;

                    default:
                        return false;
                        break;
                    }
                
                } while (1);
                
                
                break;
            case '\0':
                printf("NULL    %s\n", token_names[token_ptr->ID]);
                if (/*exp_brack && token_ptr->ID == TOKEN_RBRACKET*/ 1) {
                    next_token_counted();
                    
                    printf("NULL    next tok %s\n", token_names[token_ptr->ID]);
                    if (ERROR) {
                        printf("ERROR\n");
                        expr_stack_free(expr_stack);
                        return_all_tokens();
                        return false;
                    }
                    if (get_index_token(token_ptr) == 0) { // not an expression
                        *final_type = expr_stack->top_item->data_type;
                        expr_stack_free(expr_stack);
                        DLL_move_active_left(dll);
                        DLL_move_active_left(dll);
                        COUNTER = 0;

                        return true;
                    }
                    else {
                        ERROR = SYNTAX_ERR;
                        expr_stack_free(expr_stack);
                        return_all_tokens();
                        return false;
                    }
                }
                expr_stack_free(expr_stack);
                ERROR = SYNTAX_ERR;
                return_all_tokens();
                return false;

                
            case 'f':
                *final_type = expr_stack->top_item->data_type;
                expr_stack_free(expr_stack);
                COUNTER = 0;
                return true; 

        }
    } while (1);
}