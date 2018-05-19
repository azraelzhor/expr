#include "expr.h"

#include <stdlib.h>

Expr* create_constant_expression(float value)
{
    Expr* e = malloc(sizeof(Expr));
    e->left = NULL;
    e->right = NULL;
    e->op = '\0';
    e->value = value;
}

Expr* create_arithmetic_expression(Expr* e1, Expr* e2, char op)
{
    Expr* e = malloc(sizeof(Expr));
    e->left = e1;
    e->right = e2;
    e->op = op;
    e->value = 0;
    return e;
}

float evaluate_expression(Expr* e)
{
    switch(e->op) {
        case '+':
            return evaluate_expression(e->left) + evaluate_expression(e->right);
            break;
        case '-':
            return evaluate_expression(e->left) - evaluate_expression(e->right);
            break;
        case '*':
            return evaluate_expression(e->left) * evaluate_expression(e->right);
            break;
        case '/':
            return evaluate_expression(e->left) / evaluate_expression(e->right);
            break;
        case '\0':
            return e->value;
            break;
        default:
            return 0;
            break;
    }
}
