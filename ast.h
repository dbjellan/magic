
#define AST_MODULE 1
#define AST_STRING_LIT 2
#define AST_INT_LIT 3
#define AST_FLOAT_LIT 4
#define AST_ASSIGN 5
#define AST_ADD 6
#define AST_SUB 7
#define AST_MULT    8
#define AST_DIV 9
#define AST_IDENTIFIER 10
#define AST_FIELD 11
#define AST_LVAL_IDENTIFIER 12
#define AST_LVAL_ACCESS 13
#define AST_FUNC    14
#define AST_FUNCTION_CALL 15
#define AST_STATEMENTS 16
#define AST_ARGLIST 17
#define AST_VARLIST 18

struct ast_node;

struct ast_node* make_string_lit(struct ast_node * a);
struct ast_node* make_int_lit(struct ast_node * a);
struct ast_node* make_float_lit(struct ast_node * a);
struct ast_node* make_identifier(struct ast_node * a);
struct ast_node* make_field(struct ast_node *a, struct ast_node *b);
struct ast_node* make_lval_identifier(struct ast_node *text);
struct ast_node* make_lval_access(struct ast_node *a, struct ast_node * b);
struct ast_node* make_assign(struct ast_node* lvalue, struct ast_node* rvalue);
struct ast_node* make_lval_identifier(char * a);
struct ast_node* make_lval_access(struct ast_node * a, struct ast_node* b); 
struct ast_node* make_add(struct ast_node * a, struct ast_node *b);
struct ast_node* make_sub(struct ast_node * a, struct ast_node *b);
struct ast_node* make_mult(struct ast_node * a, struct ast_node *b);
struct ast_node* make_div(struct ast_node* a, struct ast_node* b);
struct ast_node* make_assign(struct ast_node* lvalue, struct ast_node* rvalue);

struct ast_node* make_func(struct ast_node *ident, struct ast_node *arglist, struct ast_node *body);
struct ast_node* make_function_call(struct ast_node *ident, struct ast_node *arglist);
struct ast_node* make_module(struct ast_node *statements);
struct ast_node* make_statements(struct ast_node *s1, struct ast_node *s2);
struct ast_node* make_varlist(struct ast_node *a, struct ast_node *b);
struct ast_node* make_arglist(struct ast_node *a, struct ast_node *b);


struct magic_object* ast_execute(m_state * state, struct ast_node* node);