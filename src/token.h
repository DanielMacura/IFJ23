
#ifndef TOKEN_H
#define TOKEN_H


typedef enum {
    TOKEN_ID_IDENTIFIER,            // functions
    TOKEN_ID_VARIABLE,              // variables
    TOKEN_ID_INTEGER,
    TOKEN_ID_FLOAT,
    TOKEN_ID_STRING,
    TOKEN_ID_KEYWORD,

    TOKEN_ID_PLUS,                  // arithmetic and concatenation
    TOKEN_ID_MINUS,
    TOKEN_ID_EQUALS,                // =
    TOKEN_ID_DOUBLE_EQUALS,         // ==
    TOKEN_ID_NOT_EQUALS,            // !=
    TOKEN_ID_GT,                    // >
    TOKEN_ID_LT,                    // <
    TOKEN_ID_GTE,                   // >=
    TOKEN_ID_LTE,                   // <=
    TOKEN_ID_QUESTIONMARK,          // ?
    TOKEN_ID_NIL_COALESCING,        // ??
    TOKEN_ID_EXCLAMATIONMARK,       // !
    TOKEN_ID_DIVISION,
    TOKEN_ID_MULTIPLICATION,
    TOKEN_ID_COMMA,
    TOKEN_ID_SEMICOLLON,
    TOKEN_ID_COLON,

    TOKEN_ID_LBRACKET,
    TOKEN_ID_RBRACKET,
    TOKEN_ID_LCURLYBRACKET,
    TOKEN_ID_RCURLYBRACKET,

    TOKEN_ID_EOL,
    TOKEN_ID_EOF,

} token_ID;



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