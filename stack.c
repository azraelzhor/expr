#include "expr.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct Stack* create_stack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = malloc(stack->capacity * sizeof(void*));
    return stack;
}

int is_full(struct Stack* stack)
{   return stack->top == stack->capacity - 1; }

int is_empty(struct Stack* stack)
{   return stack->top == -1;  }

void push(struct Stack* stack, void* item)
{
    if (is_full(stack))
        return;
    stack->array[++stack->top] = item;
}

void* pop(struct Stack* stack)
{
    if (is_empty(stack))
        return NULL;
    return stack->array[stack->top--];
}

void* top(struct Stack* stack)
{
    if (is_empty(stack))
        return NULL;
    return stack->array[stack->top];
}
