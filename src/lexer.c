#include "lexer.h"


lexer_T *lexer_init() {
    lexer_T *lexer = calloc(1, sizeof(struct lexer_struct));

    lexer->state = STATE_START;
    lexer->i = 0;
    lexer_advance(lexer);

    return lexer;
}

void lexer_free(lexer_T *lexer) {
    free(lexer);
}

void lexer_advance(lexer_T *lexer) {
    if (lexer->c != EOF) {
        lexer->i += 1;
        lexer->c = getc(stdin);
    }
}

void lexer_skip_whitespace(lexer_T *lexer) {
    while (lexer->c == ' ' || lexer->c == '\r' || lexer->c == '\t' || lexer->c == '\n') {
        lexer_advance(lexer);
    }
}

int is_keyword(char *src) {
    
    if (!strcmp(src, "Double")) {
        return KW_DOUBLE;
    }
    else if (!strcmp(src, "else")) {
        return KW_ELSE;
    }
    else if (!strcmp(src, "func")) {
        return KW_FUNC;
    }
    else if (!strcmp(src, "if")) {
        return KW_IF;
    }
    else if (!strcmp(src, "Int")) {
        return KW_INT;
    }
    else if (!strcmp(src, "let")) {
        return KW_LET;
    }
    else if (!strcmp(src, "nil")) {
        return KW_NIL;
    }
    else if (!strcmp(src, "return")) {
        return KW_RETURN;
    }
    else if (!strcmp(src, "String")) {
        return KW_STRING;
    }
    else if (!strcmp(src, "var")) {
        return KW_VAR;
    }
    else if (!strcmp(src, "while")) {
        return KW_WHILE;
    }
    return 0;
}




void clean_string(char **str) {
    size_t str_len = strlen(*str);

    char *new_str = chararray_init(str_len +1);
    if (new_str == NULL) {
        // TODO error
    }

    size_t i;
    size_t n_i = 0;
    for (i = 0; i < str_len; i++)
    {
        char c = (char)0;

        if ((*str)[i] == '\\') {
            switch ((*str)[i + 1]) {
            case 'u':
                if (i + 5 < str_len && (*str)[i + 2] == '{' && isxdigit((*str)[i + 3]) && isxdigit((*str)[i + 4]) && (*str)[i + 5] == '}') {
                    char hex[3] = {(*str)[i + 3], (*str)[i + 4], '\0'};
                    int num = (int)strtol(hex, NULL, 16);
                    if (num >= 0x01 && num <= 0xFF) { // check if the number is in the range of 1-255
                        c = num;
                        i += 5;
                    }
                    else {
                        c = (*str)[i];
                    }
                }
                break;
            case '"':
                c = '"';
                i++;
                break;
            case 'n':
                c = '\n';
                i++;
                break;
            case 't':
                c = '\t';
                i++;
                break;
            case 'r':
                c = '\r';
                i++;
                break;
            case '\\':
                c = '\\';
                i++;
                break;
            default:
                c = (*str)[i]; // take the backslash
                break;
            }
        }
        else {
            c = (*str)[i];
        }
        new_str[n_i++] = c;
    }

    char *str_final = chararray_init(4*strlen(new_str) +1);
    for (i = 0; i < strlen(new_str); i++)
    {
        char num[7] = {(char)0};
        char c_as_string[2];

        c_as_string[0] = new_str[i];
        c_as_string[1] = '\0';

        if ((new_str[i] >= 0 && new_str[i] <= 32) || new_str[i] == 35 || new_str[i] == 92) { // 0-32, 35, 92
            sprintf(num, "\\0%d", new_str[i]);
            strcat(str_final, num);
        } else {
            strcat(str_final, c_as_string);
        }
    }

    chararray_free(new_str);
    chararray_free(*str);

    *str = str_final;
}

error lexer_next_token(lexer_T *lexer, token *Token) {

 char *value = chararray_init(0);
    unsigned int char_i; // used eg char_i=lexer->i to track number of loaded characters

    while (1) {
        switch (lexer->state) {

        case STATE_START:
            lexer_skip_whitespace(lexer);

            if (isalpha(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_IDENTIFIER_START;
            }
            else if (lexer->c == '_') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_IDENTIFIER_UNDERSCORE;
            }
            else if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_E;
            }

            else if (lexer->c == '?') {
                lexer_advance(lexer);
                lexer->state = STATE_QUESTIONMARK;
            }

            else if (lexer->c == '!') {
                lexer_advance(lexer);
                lexer->state = STATE_NOT;
            }

            else if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_EQ_E;
            }
            else if (lexer->c == '>') {
                lexer_advance(lexer);
                lexer->state = STATE_GT_E;
            }
            else if (lexer->c == '<') {
                lexer_advance(lexer);
                lexer->state = STATE_ST_E;
            }

            else if (lexer->c == '+') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_PLUS;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }
            else if (lexer->c == '-') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_MINUS;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }
            else if (lexer->c == '*') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_MULTIPLICATION;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == '/') {
                lexer->state = STATE_SLASH;
                // without lexer advance. lexer_skip_comment takes care
            }

            else if (lexer->c == '"') {
                lexer_advance(lexer);
                lexer->state = STATE_QUOTATION_CENTER_E;
                break;
            }

            else if (lexer->c == '(') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_LBRACKET;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == ')') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_RBRACKET;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }
            else if (lexer->c == '{') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_LCURLYBRACKET;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == '}') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_RCURLYBRACKET;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == ',') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_COMMA;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == ':') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_COLON;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }

            else if (lexer->c == EOF) {
                Token->ID = TOKEN_ID_EOF;
                Token->VAL.string = value;
                return SUCCESS;
            }

            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_IDENTIFIER_START:
            if (isalnum(lexer->c) || lexer->c == '_') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_IDENTIFIER_E;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_IDENTIFIER;
                Token->VAL.string = value;
                
                return SUCCESS;
            }
            break;
        
        case STATE_IDENTIFIER_UNDERSCORE:
            if (isalnum(lexer->c) || lexer->c == '_') {
                    chararray_append(&value, lexer->c);
                    lexer_advance(lexer);

                }
            else {
                    lexer_advance(lexer);
                    return LEXICAL_ERR;
                }
            break;

        case STATE_IDENTIFIER_E:
            if (isalnum(lexer->c) || lexer->c == '_') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else {
                keyword kw = is_keyword(value);
                if (kw) {
                    lexer->state = STATE_START;
                    Token->ID = TOKEN_ID_KEYWORD;
                    Token->VAL.keyword = kw;
                    return SUCCESS;

                }
                else {
                    lexer->state = STATE_START;
                    Token->ID = TOKEN_ID_IDENTIFIER;
                    Token->VAL.string = value;
                    
                    return SUCCESS;
                }
            }
            break;


        case STATE_INTEGER_E:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else if (lexer->c == '.') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_AND_SEPARATOR;
            }
            else if (tolower(lexer->c) == 'e') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_EXPONENT_START;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_INTEGER;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_INTEGER_AND_SEPARATOR:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_DOUBLE_E;
                break;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_DOUBLE_E:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else if (tolower(lexer->c) == 'e') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_DOUBLE_EXPONENT_START;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_FLOAT;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_INTEGER_EXPONENT_START:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_EXPONENT_E;
            }
            else if (lexer->c == '+' || lexer->c == '-') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_EXPONENT_SIGN;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_INTEGER_EXPONENT_SIGN:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_INTEGER_EXPONENT_E;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_INTEGER_EXPONENT_E:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_INTEGER;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_DOUBLE_EXPONENT_START:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_DOUBLE_EXPONENT_E;
            }
            else if (lexer->c == '+' || lexer->c == '-') {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_DOUBLE_EXPONENT_SIGN;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_DOUBLE_EXPONENT_SIGN:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
                lexer->state = STATE_DOUBLE_EXPONENT_E;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_DOUBLE_EXPONENT_E:
            if (isdigit(lexer->c)) {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_INTEGER;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_NOT:
            if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_NOT_EQ;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_NOT_EQ:
            if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_NOT_EQUALS;
                Token->VAL.string = value;
                return SUCCESS;
            }
            else {
                lexer_advance(lexer);
                return LEXICAL_ERR;
            }
            break;

        case STATE_EQ_E:
            if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_DOUBLE_EQUALS;
                Token->VAL.string = value;
                return SUCCESS;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_EQUALS;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_GT_E:
            if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_GTE;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_GT;
            }
            Token->VAL.string = value;
            return SUCCESS;

        case STATE_ST_E:
            if (lexer->c == '=') {
                lexer_advance(lexer);
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_LTE;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_LT;
            }
            Token->VAL.string = value;
            return SUCCESS;

        case STATE_QUOTATION_CENTER_E:
            if (lexer->c == '"') {
                lexer_advance(lexer);
                if (lexer->c == '"'){
                    lexer_advance(lexer);
                    lexer->state = STATE_QUOTATION_TRIPLE_E;
                }
                else{
                    lexer->state = STATE_START;
                    clean_string(&value);
                    Token->ID = TOKEN_ID_STRING;
                    Token->VAL.string = value;
                    return SUCCESS;
                }
            }
            else if (lexer->c == '\\') {
                lexer->state = STATE_QUOTATION_ESCAPE_CHAR;
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            else {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            break;
        case STATE_QUOTATION_TRIPLE_E:
            if (lexer->c == '"') {
                lexer_advance(lexer);
                if (lexer->c == '"'){
                    lexer_advance(lexer);
                    if (lexer->c == '"'){
                        lexer_advance(lexer);
                        lexer->state = STATE_START;
                        clean_string(&value);
                        Token->ID = TOKEN_ID_STRING;
                        Token->VAL.string = value;
                        return SUCCESS;
                    }
                    else{
                        chararray_append(&value, lexer->c);
                        lexer_advance(lexer);
                }
                }
                else{
                    chararray_append(&value, lexer->c);
                    lexer_advance(lexer);
                }
            }
            else {
                chararray_append(&value, lexer->c);
                lexer_advance(lexer);
            }
            break;

        case STATE_QUOTATION_ESCAPE_CHAR:
            lexer->state = STATE_QUOTATION_CENTER_E;
            chararray_append(&value, lexer->c);
            lexer_advance(lexer);
            break;

        case STATE_SLASH:
            char_i = lexer->i;
            //lexer_skip_comment(lexer);
            lexer->state = STATE_START;
            if (lexer->i - char_i == 1) { // moved just one character ie no comment skipped
                Token->ID = TOKEN_ID_DIVISION;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_QUESTIONMARK:
            if (lexer->c == '?') {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_NIL_COALESCING;
                Token->VAL.string = value;
                lexer_advance(lexer);
                return SUCCESS;
            }
            else {
                lexer->state = STATE_START;
                Token->ID = TOKEN_ID_QUESTIONMARK;
                Token->VAL.string = value;
                return SUCCESS;
            }
            break;

        case STATE_CLOSING_TAG:
            if (lexer->c == EOF)
                lexer->state = STATE_START;
            else {
                lexer->state = STATE_START;
                lexer_advance(lexer);
                return SYNTAX_ERR; // syntactic error
            }
            break;
        }
    }
}