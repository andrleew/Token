#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "Token.h"

bool is_operator(int c){
    switch(c){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
        default:
            return false;
    }
}
bool is_value(int c){
    return ((c - '0' < 10) && (c - '0' > -1));
}
bool is_char(int c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c<= 'z'));
}
bool is_bracket(int c){
    return (c == '(' || c == ')');
}

int token_priority(Token token){
    switch(token.value){
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
        return 1;
    case '^':
        return 2;
    default:
        return -1;
    }
}

int priority(Token token1, Token token2){
    return token1.value == '^' && token2.value == '^' ? -1: token_priority(token1) - token_priority(token2);
}

bool is_right(Token token){
    return token.type == TOKEN_OPERATOR && token.value != '^';
}

Token read_token(){
    int c = getchar();
    while (isspace(c) && c != EOF && c != '\n' &&
           !is_operator(c) && !is_value(c) &&
           !is_char(c) &&  !is_bracket(c)) c = getchar();
    Token token;
    if (is_operator(c)){
        token.type = TOKEN_OPERATOR;
        token.value = c;
    }else if (is_value(c)){
        token.type = TOKEN_NUMBER;
        ungetc(c, stdin);
        scanf("%d", &token.value);
    }else if (is_char(c)){
        token.type = TOKEN_CHAR;
        token.value = c;
    }else if (c == '('){
        token.type = TOKEN_LEFT_BRACKET;
        token.value = c;
    }else if (c == ')'){
        token.type = TOKEN_RIGHT_BRACKET;
        token.value = c;
    }else{
        token.type = TOKEN_NONE;
        token.value = 0;
    }
    return token;
}

void print_token(Token token){
    switch(token.type){
    case TOKEN_OPERATOR:
        printf(" %c ", token.value);
        break;
    case TOKEN_NUMBER:
        if (token.value < 0) printf("(");
        printf("%d", token.value);
        if (token.value < 0) printf(")");
        break;
    case TOKEN_CHAR:
        printf("%c", token.value);
        break;
    case TOKEN_UNAR_MINUS:
        printf("(-%c)", token.value);
        break;
    default:
        break;
    }
}
