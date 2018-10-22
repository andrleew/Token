#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Token_tree_stack.h"

bool is_empty_tts(Token_tree_stack * tts){
    return tts->first == NULL;
}

Token_tree_stack * create_t_t_s(){
    Token_tree_stack * t_t_s = (Token_tree_stack*)malloc(sizeof(Token_tree_stack));
    t_t_s->first = NULL;
    return t_t_s;
}

bool add_token_tree(Token_tree_stack * tts, Token_tree * tt){
    TS_Element * new_el = (TS_Element*)malloc(sizeof(TS_Element));
    if(!new_el) return false;
    new_el->next = tts->first;
    new_el->token_tree = tt;
    tts->first = new_el;
    return true;
}

Token_tree * pop_tts(Token_tree_stack * tts){
    TS_Element * tse = tts->first;
    Token_tree * tt = tse->token_tree;
    tts->first = tts->first->next;
    free(tse);
    return tt;
}

void destroy_tts(Token_tree_stack * tts){
    while (!is_empty_tts(tts)){
        pop_tts(tts);
    }
    free(tts);
}
