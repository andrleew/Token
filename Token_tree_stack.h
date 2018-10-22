#ifndef TOKEN_TREE_STACK_H_INCLUDED
#define TOKEN_TREE_STACK_H_INCLUDED


#include <stdbool.h>

#include "Token.h"
#include "Token_tree.h"

typedef struct TS_Element{
    struct TS_Element * next;
    Token_tree * token_tree;
}TS_Element;

typedef struct{
    TS_Element * first;
}Token_tree_stack;

bool is_empty_tts(Token_tree_stack * tts);
Token_tree_stack * create_t_t_s();
bool add_token_tree(Token_tree_stack * tts, Token_tree * tt);
Token_tree * pop_tts(Token_tree_stack * tts);
void destroy_tts(Token_tree_stack * tts);

#endif // TOKEN_TREE_STACK_H_INCLUDED
