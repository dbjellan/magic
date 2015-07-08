
#define AST_MODULE 1
#define AST_STRING_LIT 2
#define AST_INT_LIT 3
#define AST_FLOAT_LIT 4
#define AST_ASSIGN 5
#define AST_ADD 6
#define AST_SUB 7
#define AST_MULT    8
#define AST_DIV 9

struct ast_node;

struct ast_node* make_assign(struct ast_node* lvalue, struct ast_node* rvalue);
struct ast_node* make_lval_identifier(char * text);