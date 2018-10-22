#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Token_queue.h"

Token_queue * create_token_queue(){
    Token_queue * t_queue = (Token_queue*)malloc(sizeof(Token_queue));
    t_queue->first = NULL;
    t_queue->last = NULL;
    return t_queue;
}

bool is_empty_tq(Token_queue * token_queue){
    return token_queue->first == NULL;
}

Token top_token_queue(Token_queue * token_queue){
    return token_queue->first->token;
}

Token pop_token_queue(Token_queue * tq){
    Queue_element * q_e = tq->first;
    Token token = q_e->token;
    tq->first = q_e->next;
    q_e = NULL;
    free(q_e);
    return token;
}

bool add_to_tq(Token_queue * tq, Token token){
    Queue_element * new_element = (Queue_element*)malloc(sizeof(Queue_element));
    if (!new_element) return false;
    new_element->token = token;
    new_element->next = NULL;
    if (tq->last != NULL) tq->last->next = new_element;
    tq->last = new_element;
    if (!tq->first) tq->first = new_element;
    return true;
}

void print_tq(Token_queue * token_queue){
    Queue_element * q1, *q2;
    q1 = token_queue->first;
    q2 = q1->next;
    while (q1 != NULL){
        print_token(q1->token);
        q1 = q2;
        if (q1 != NULL)
            q2 = q1->next;
    }
}

void destroy_token_queue(Token_queue *  tq){
    while (!is_empty_tq(tq)){
        pop_token_queue(tq);
    }
}
