#ifndef TOKEN_STACK_H_INCLUDED
#define TOKEN_STACK_H_INCLUDED

#include <stdbool.h>

#include "Token.h"

typedef struct Stack_element{
    struct Stack_element * next;
    Token token;
}Stack_element;

typedef struct{
    Stack_element * first;
}Token_stack;

Token_stack * create_t_s();
bool is_empty_ts(Token_stack * ts);
Token top_token_stack(Token_stack * ts);
bool add_to_token_stack(Token_stack * t_s, Token token);
Token del_from_token_stack(Token_stack * t_s);
void destroy_token_stack(Token_stack * ts);

#endif // TOKEN_STACK_H_INCLUDED
