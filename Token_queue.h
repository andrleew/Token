#ifndef TOKEN_QUEUE_H_INCLUDED
#define TOKEN_QUEUE_H_INCLUDED


#include <stdbool.h>

#include "Token.h"

typedef struct Queue_element{
    struct Queue_element * next;
    Token token;
}Queue_element;

typedef struct{
    Queue_element * first;
    Queue_element * last;
}Token_queue;

Token_queue * create_token_queue();
bool is_empty_tq(Token_queue * token_queue);
Token top_token_queue(Token_queue * token_queue);
Token pop_token_queue(Token_queue * tq);
bool add_to_tq(Token_queue * tq, Token token);
void print_tq(Token_queue * token_queue);
void destroy_token_queue(Token_queue *  tq);

#endif // TOKEN_QUEUE_H_INCLUDED
