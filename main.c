#include "expr.h"
#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int MAX_LENGTH = 100;

int is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' ||c == '/')
        return 1;
    return 0;
}

int is_number(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '(' || op == ')')
        return 3;
}

int check_valid(char* expr)
{
    int length = strlen(expr);

    if (length < 3)
        return 0;

    if (is_number(expr[0]))
    {
        if (expr[1] == '(')
            return 0;
    }
    for (int i = 1; i < length; i++)
    {
        if (is_operator(expr[i]))
        {
            if (is_operator(expr[i-1]) || is_operator(expr[i+1]))
                return 0;
            if (expr[i-1] == '(' || expr[i+1] == ')')
                return 0;
        }
        else if (is_number(expr[i]))
        {
            if (expr[i-1] == ')' || expr[i+1] == '(')
                return 0;
        }
    }
    return 1;
}

void from_infix_to_postfix(char* str, char* out, int* success)
{
    if (!check_valid(str))
    {
        *success = 0;
        printf("Invalid expression!\n");
        return;
    }

    int length = strlen(str);
    Stack* op_stack = create_stack(length);

    int start = 0, end = 0, idx = 0, prev = 0;
    char op, top_op;
    for (int i = 0; i < length; i++)
    {
        if (is_operator(str[i]))
        {
            if (prev == 1)
            {
                *success = 0;
                printf("Invalid expression!\n");
                return;
            }
            prev = 1;
            out[idx++] = ' ';
            start = i;
            end = i;
            while(!is_empty(op_stack))
            {
                top_op = *(char*)top(op_stack);
                if (priority(top_op) < priority(str[i]))
                {
                    push(op_stack, str + i);
                    break;
                }
                else if (top_op != '(')
                {
                    top_op = *(char*)pop(op_stack);
                    out[idx++] = top_op;
                    out[idx++] = ' ';
                }
                else
                {
                    push(op_stack, str + i);
                    break;
                }
            }
            if (is_empty(op_stack))
            {
                push(op_stack, str + i);
            }
        }
        else if (str[i] == '(')
        {
            prev = 0;
            push(op_stack, str + i);
        }
        else if (str[i] == ')')
        {
            prev = 0;
            op = ' ';
            while (!is_empty(op_stack))
            {
                op = *(char*)pop(op_stack);
                if (op != '(')
                {
                    out[idx++] = ' ';
                    out[idx++] = op;
                }
                else
                {
                    break;
                }
            }
            if (op != '(')
            {
                *success = 0;
                printf("Invalid expression!\n");
                return;
            }
        }
        else
        {
            prev = 0;
            end++;
            out[idx++] = str[i];
        }
    }
    while (!is_empty(op_stack))
    {
        op = *(char*)pop(op_stack);
        if (op == '(' || op == ')')
        {
            *success = 0;
            printf("Invalid expression!\n");
            return;
        }
        out[idx++] = ' ';
        out[idx++] = op;
    }
    out[idx++] = '\0';
    return;
}

Expr* from_postfix_to_expression(char* str)
{
    const char delim[2] = " ";
    char* token;
    char* end;
    int idx = 0;

    int length = strlen(str);
    Stack* expr_stack = create_stack(length);
    char operators[length];

    token = strtok(str, delim);

    while (token != NULL)
    {
        if (strlen(token) == 1 && is_operator(token[0]))
        {
            operators[idx++] = token[0];
            Expr* e2 = (Expr*)pop(expr_stack);
            Expr* e1 = (Expr*)pop(expr_stack);
            if (e1 == NULL || e2 == NULL)
            {
             printf("Invalid expression!\n");
             return NULL;
            }
            Expr* e = create_arithmetic_expression(e1, e2, token[0]);
            push(expr_stack, e);
        } else {
            float val = strtof(token, &end);
            if (end[0] != '\0')
            {
                printf("Invalid expression!\n");
                return NULL;
            }
            else
            {
                Expr* e = create_constant_expression(val);
                push(expr_stack, e);
            }
        }
        token = strtok(NULL, delim);
    }

    Expr* expr = (Expr*)pop(expr_stack);
    if (!is_empty(expr_stack))
    {
        printf("Invalid expression!\n");
        return NULL;
    }

    return expr;
}

int main()
{
    char str[MAX_LENGTH];
    printf("Input your infix arithmetic expression:\n");
    scanf("%s", str);

    char postfix[MAX_LENGTH];
    int success = 1;

    from_infix_to_postfix(str, postfix, &success);

    Expr* result = NULL;
    if (success)
        result = from_postfix_to_expression(postfix);

    if (result != NULL)
        printf("Value of your expression is %.2f\n", evaluate_expression(result));

    return 0;
}
