#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Token.h"
#include "Token_queue.h"
#include "Token_stack.h"
#include "Token_tree.h"
#include "Token_tree_stack.h"


void make_tree(Token_queue * token_queue, Token_tree * token_tree){
    Token_tree_stack * token_tree_stack = create_t_t_s();
    while (!is_empty_tq(token_queue)){
        Token token = pop_token_queue(token_queue);
        Token_tree * tt = create_token_tree();
        if (token.type == TOKEN_NUMBER ||
            token.type == TOKEN_CHAR ||
            token.type == TOKEN_UNAR_MINUS){
            add_to_token_tree(tt, token, -1);
            add_token_tree(token_tree_stack, tt);
        }else if(token.type == TOKEN_OPERATOR){
            add_to_token_tree(tt, token, -1);
            if (!is_empty_tts(token_tree_stack))
                add_tt_to_tt(tt, pop_tts(token_tree_stack),0);
            if (!is_empty_tts(token_tree_stack))
                add_tt_to_tt(tt, pop_tts(token_tree_stack),1);
            add_token_tree(token_tree_stack, tt);
        }
    }
    add_tt_to_tt(token_tree, pop_tts(token_tree_stack), -1);
}

bool dijkstra(Token_queue * output_queue){
    Token token = read_token();
    Token_stack * operator_stack = create_t_s();
    int prev_type = TOKEN_NONE;
    bool unary = false;
    while (token.type != TOKEN_NONE){
        switch(token.type){
        case TOKEN_NUMBER:
            if(unary){
                token.value *= -1;
                unary = false;
            }
            if (prev_type == TOKEN_NUMBER ||
                prev_type == TOKEN_CHAR ||
                prev_type == TOKEN_UNAR_MINUS ||
                prev_type == TOKEN_RIGHT_BRACKET)
                return false;
            add_to_tq(output_queue, token);
            break;
        case TOKEN_CHAR:
            if (unary){
                token.type = TOKEN_UNAR_MINUS;
                unary = false;
            }
            if (prev_type == TOKEN_NUMBER ||
                prev_type == TOKEN_CHAR ||
                prev_type == TOKEN_UNAR_MINUS)
                return false;
            add_to_tq(output_queue, token);
            break;
        case TOKEN_OPERATOR:
            if (token.value == '-' &&
                (prev_type == TOKEN_NONE ||
                 prev_type == TOKEN_LEFT_BRACKET ||
                 prev_type == TOKEN_OPERATOR)){
                    unary = true;
                    break;
            }
            if(prev_type == TOKEN_OPERATOR ||
               prev_type == TOKEN_LEFT_BRACKET) return false;
            while (!is_empty_ts(operator_stack) && top_token_stack(operator_stack).value != '('){
                Token operator = top_token_stack(operator_stack);
                if ((is_right(token) && priority(token, operator) < 0) ||
                    (!is_right(token) && priority(token, operator) <= 0)){
                        add_to_tq(output_queue, del_from_token_stack(operator_stack));
                }
                else break;
            }
            add_to_token_stack(operator_stack, token);
            break;
        case TOKEN_LEFT_BRACKET:
            if (prev_type == TOKEN_NUMBER ||
                prev_type == TOKEN_CHAR ||
                prev_type == TOKEN_UNAR_MINUS)
                return false;
            add_to_token_stack(operator_stack, token);
            break;
        case TOKEN_RIGHT_BRACKET:
            if(prev_type == TOKEN_OPERATOR) return false;
            while (!is_empty_ts(operator_stack) && top_token_stack(operator_stack).value != '('){
                add_to_tq(output_queue, del_from_token_stack(operator_stack));
            }
            if (is_empty_ts(operator_stack))
                return false;
            else if (top_token_stack(operator_stack).value == '(')
                del_from_token_stack(operator_stack);
            break;
        default:
            break;
        }
        prev_type = token.type;
        token = read_token();
    }
    while(!is_empty_ts(operator_stack)){
        if (top_token_stack(operator_stack).value == '(')
            return false;
        add_to_tq(output_queue, del_from_token_stack(operator_stack));
    }
    return true;
}

void search_node(Node ** node){
    if (token_priority((*node)->token) == 1 &&
        (*node)->right != NULL &&
        (*node)->left != NULL){
                if ((*node)->right->token.type == TOKEN_OPERATOR){
                    if (priority((*node)->token, (*node)->right->token) > 0 &&
                        (*node)->right->right != NULL &&
                        (*node)->right->left != NULL){
                            Node * root = (Node*)malloc(sizeof(Node));
                            Node * left = (Node*)malloc(sizeof(Node));
                            Node * right = (Node*)malloc(sizeof(Node));
                            root->token = (*node)->right->token;
                            right->token = (*node)->token;
                            left->token = (*node)->token;
                            right->left = (*node)->left;
                            right->right = (*node)->right->right;
                            left->left = (*node)->left;
                            left->right = (*node)->right->left;
                            root->left = left;
                            root->right = right;
                            *node = root;
                        }
                }else if ((*node)->left->token.type == TOKEN_OPERATOR){
                    if (priority((*node)->token, (*node)->left->token) > 0 &&
                        (*node)->left->right != NULL &&
                        (*node)->left->left != NULL){
                            Node * root = (Node*)malloc(sizeof(Node));
                            Node * left = (Node*)malloc(sizeof(Node));
                            Node * right = (Node*)malloc(sizeof(Node));
                            root->token = (*node)->left->token;
                            right->token = (*node)->token;
                            left->token = (*node)->token;
                            left->right = (*node)->right;
                            left->left = (*node)->left->left;
                            right->right = (*node)->right;
                            right->left = (*node)->left->right;
                            root->left = left;
                            root->right = right;
                            *node = root;
                        }
                }
    }
    if ((*node)->left != NULL) search_node(&((*node)->left));
    if ((*node)->right != NULL) search_node(&((*node)->right));
}

void change(Token_tree * token_tree){
    search_node(&token_tree->root);
}
int count (Node * node){
int k = 0;
if (node->token.type == TOKEN_CHAR ||
node->token.type == TOKEN_NUMBER ||
node->token.type == TOKEN_UNAR_MINUS)
k++;
if (node->left) k += count(node->left);
if (node->right) k += count (node->right);
return k;
}

int operand(Token_tree * tt){
return count (tt->root);
}

int main(){
    Token_queue * tq2 = create_token_queue();
    if (!dijkstra(tq2)){
        destroy_token_queue(tq2);
        printf("Error\n");
        return 1;
    }
    Token_tree * tt = create_token_tree();
    printf("poland\n");
    print_tq(tq2);
    printf("\n");
    make_tree(tq2, tt);
    printf("Token tree\n");
    print_token_tree(tt);
    printf("\n%d\n", operand(tt));
    printf("\n");
    return 0;
}
