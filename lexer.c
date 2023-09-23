#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                lexer->state = STATE_START;
                lexer_advance(lexer);
                //clean_string(&value);
                Token->ID = TOKEN_ID_STRING;
                Token->VAL.string = value;
                return SUCCESS;
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