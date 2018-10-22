#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Token_tree.h"

Token_tree* create_token_tree(){
    Token_tree * tt = (Token_tree*)malloc(sizeof(Token_tree));
    tt->root = NULL;
    return tt;
}

bool is_empty_token_tree(Token_tree * tt){
    return tt->root == NULL;
}

bool add_to_token_tree(Token_tree * tt, Token token, int place){
    Node * node = (Node*)malloc(sizeof(Node));
    if (!node) return false;
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    if (place == -1) tt->root = node;
    else{
        Node ** place_node = &(tt->root);
        int a = 10;
        do{
            if (place % a == 0){
                place_node = &(*place_node)->right;
            }
            else{
                place_node = &(*place_node)->left;
            }
            place -= place % a;
            a *= 10;
        }while (place > 0);
        *place_node = node;
    }
    return true;
}

void add_tt_to_tt (Token_tree * tree1, Token_tree * tree2, int place){
    switch(place){
    case 0:
        tree1->root->right = tree2->root;
        break;
    case 1:
        tree1->root->left = tree2->root;
        break;
    default:
        tree1->root = tree2->root;
    }
}

void print_nodes(Node * node){
    bool bracket = false;
    if (node->left != NULL){
        if (node->left->token.type == TOKEN_OPERATOR)
            if (priority(node->token, node->left->token) > 0)
                bracket = true;
        if (bracket) printf("(");
        print_nodes(node->left);
        if (bracket) printf(")");
    }
    print_token(node->token);
    if (node->right != NULL){
        bracket = false;
        if (node->right->token.type == TOKEN_OPERATOR)
            if (priority(node->token, node->right->token) > 0)
                bracket = true;
        if (bracket) printf("(");
        print_nodes(node->right);
        if (bracket) printf(")");
    }
}

void print_token_tree(Token_tree * tt){
    print_nodes(tt->root);
}

void destroy_node(Node * node){
    if(node->left) destroy_node(node->left);
    node->left = NULL;
    if(node->right) destroy_node(node->right);
    node->right = NULL;
    free(node);
}

void destroy_token_tree(Token_tree * tt){
    destroy_node(tt->root);
    free(tt);
}
