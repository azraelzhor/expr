typedef struct Stack
{
    int top;
    unsigned capacity;
    void** array;
} Stack;

Stack* create_stack(unsigned capacity);
void push(struct Stack* stack, void* item);
void* pop(struct Stack* stack);
int is_empty(struct Stack* stack);
void* top(struct Stack* stack);
