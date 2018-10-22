#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Token_stack.h"

Token_stack * create_t_s(){
    Token_stack * t_s = (Token_stack*)malloc(sizeof(Token_stack));
    t_s->first = NULL;
    return t_s;
}

bool is_empty_ts(Token_stack * ts){
    return ts->first == NULL;
}

Token top_token_stack(Token_stack * ts){
    return ts->first->token;
}

bool add_to_token_stack(Token_stack * t_s, Token token){
    Stack_element * s_e = (Stack_element*)malloc(sizeof(Stack_element));
    if (!s_e) return false;
    s_e->token = token;
    s_e->next = t_s->first;
    t_s->first = s_e;
    return true;
}

Token del_from_token_stack(Token_stack * t_s){
    Stack_element * s_e = t_s->first;
    Token t = s_e->token;
    t_s->first = s_e->next;
    free(s_e);
    return t;
}

void destroy_token_stack(Token_stack * ts){
    while (!is_empty_ts(ts)){
        del_from_token_stack(ts);
    }
}
