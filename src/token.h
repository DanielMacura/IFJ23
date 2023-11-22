
#ifndef TOKEN_H
#define TOKEN_H


typedef enum {
    TOKEN__EPSILON,
    TOKEN_KW_FUNC,
    TOKEN_IDENTIFIER,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_ARROW,
    TOKEN_LCURLYBRACKET,
    TOKEN_RCURLYBRACKET,
    TOKEN_KW_IF,
    TOKEN_KW_ELSE,
    TOKEN_KW_WHILE,
    TOKEN_KW_RETURN,
    TOKEN_EOL,
    TOKEN_KW_VAR,
    TOKEN_VARIABLE,
    TOKEN_KW_LET,
    TOKEN_COLON,
    TOKEN_EQUALS,
    TOKEN_QUESTIONMARK,
    TOKEN_KW_INT,
    TOKEN_KW_DOUBLE,
    TOKEN_KW_STRING,
    TOKEN_KW_NIL,
    TOKEN_EOF,
    TOKEN_SEMICOLLON,
    TOKEN_COMMA,
    TOKEN_UNDERSCORE,

    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DOUBLE_EQUALS,
    TOKEN_NOT_EQUALS,
    TOKEN_GT,          
    TOKEN_LT,            
    TOKEN_GTE,             
    TOKEN_LTE,    
    TOKEN_NIL_COALESCING,
    TOKEN_DIVISION,
    TOKEN_MULTIPLICATION,     
    TOKEN_EXCLAMATIONMARK
} token_ID;

extern const char *token_names[];

typedef enum {
    KW_NO_KW,
    KW_DOUBLE,
    KW_ELSE,
    KW_FUNC,
    KW_IF,
    KW_INT,
    KW_LET,
    KW_NIL,
    KW_RETURN,
    KW_STRING,
    KW_VAR,
    KW_WHILE,
} keyword;


typedef union {
    int integer;            //0
    double decimal;         //1
    char *string;           //2
    keyword keyword;        //3
} token_VAL;

typedef struct
{
    token_ID ID;
    token_VAL VAL;
    
} token;

#endif