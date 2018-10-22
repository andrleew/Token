#ifndef TOKEN_TREE_H_INCLUDED
#define TOKEN_TREE_H_INCLUDED

#include <stdbool.h>

#include "Token.h"

typedef struct Node{
    struct Node * left;
    struct Node * right;
    Token token;
}Node;

typedef struct{
    Node * root;
}Token_tree;

Token_tree* create_token_tree();
bool is_empty_token_tree(Token_tree * tt);
bool add_to_token_tree(Token_tree * tt, Token token, int place);
void add_tt_to_tt (Token_tree * tree1, Token_tree * tree2, int place);
void print_token_tree(Token_tree * tt);
void destroy_token_tree(Token_tree * tt);

#endif
