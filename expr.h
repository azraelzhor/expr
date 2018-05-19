typedef struct Expr
{
    char op;
    struct Expr* left;
    struct Expr* right;
    float value;
} Expr;

Expr* create_constant_expression(float value);
Expr* create_arithmetic_expression(Expr* e1, Expr* e2, char op);
float evaluate_expression(Expr* e);
