#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <stdbool.h>

typedef enum{
    TOKEN_NONE,
    TOKEN_OPERATOR,
    TOKEN_UNAR_MINUS,
    TOKEN_NUMBER,
    TOKEN_CHAR,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
}TOKEN;

typedef struct{
    TOKEN type;
    int value;
}Token;

int token_priority(Token token);
int priority(Token token1, Token token2);
bool is_right(Token token);
Token read_token();
void print_token(Token token);

#endif // TOKEN_H_INCLUDED
