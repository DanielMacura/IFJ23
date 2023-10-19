
#ifndef TOKEN_H
#define TOKEN_H


typedef enum {
    TOKEN_EOF,               // 0
    TOKEN_EOL,               // 1
    TOKEN_IDENTIFIER,        // 2 functions
    TOKEN_VARIABLE,          // 3 variables
    TOKEN_INTEGER,           // 4
    TOKEN_FLOAT,             // 5
    TOKEN_STRING,            // 6
    TOKEN_KEYWORD,           // 7

    TOKEN_PLUS,              // 8    + arithmetic and concatenation
    TOKEN_MINUS,             // 9    -
    TOKEN_EQUALS,            // 10   =
    TOKEN_DOUBLE_EQUALS,     // 11   ==
    TOKEN_NOT_EQUALS,        // 12   !=
    TOKEN_GT,                // 13   >
    TOKEN_LT,                // 14   <
    TOKEN_GTE,               // 15   >=
    TOKEN_LTE,               // 16   <=
    TOKEN_ARROW,             // 17   ->
    TOKEN_QUESTIONMARK,      // 18   ?
    TOKEN_NIL_COALESCING,    // 19   ??
    TOKEN_EXCLAMATIONMARK,   // 20   !
    TOKEN_DIVISION,          // 21   /
    TOKEN_MULTIPLICATION,    // 22   *
    TOKEN_COMMA,             // 23   ,
    TOKEN_SEMICOLLON,        // 24   ;
    TOKEN_COLON,             // 25   :

    TOKEN_LBRACKET,          // 26   (
    TOKEN_RBRACKET,          // 27   )
    TOKEN_LCURLYBRACKET,     // 28   {
    TOKEN_RCURLYBRACKET,     // 29   }

    TOKEN_KW_DOUBLE,         // 30
    TOKEN_KW_ELSE,           // 31
    TOKEN_KW_FUNC,           // 32
    TOKEN_KW_IF,             // 33
    TOKEN_KW_INT,            // 34
    TOKEN_KW_LET,            // 35
    TOKEN_KW_NIL,            // 36
    TOKEN_KW_RETURN,         // 37
    TOKEN_KW_STRING,         // 38
    TOKEN_KW_VAR,            // 39
    TOKEN_KW_WHILE,          // 40


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