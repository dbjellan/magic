
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
#define AST_FUNCTION    14
#define AST_FUNCTION_CALL 15
#define AST_STATEMENTS 16
#define AST_ARGLIST 17
#define AST_VARLIST 18
#define AST_ACCESS 19

#define AST_IF_ELSE 20
#define AST_IF 21
#define AST_FOR 22
#define AST_WHILE 23
#define AST_TRY_CATCH 24
#define AST_THROW 25
#define AST_ELSE 26
#define AST_ELSEIF 27
#define AST_ELSEIF_ELSE 28
#define AST_KVP 29
#define AST_KVPLIST 30
#define AST_TABLE 31

struct ast_node;

struct ast_node* make_ast_node(int numchildren, int type);
struct ast_node* make_internal_node(int type, struct ast_node* a);
struct ast_node* make_internal_node(int type, struct ast_node* a, struct ast_node* b);
struct ast_node* make_internal_node(int type, struct ast_node* a, struct ast_node* b, struct ast_node* c);

struct ast_node* make_string_lit(struct ast_node * a);
struct ast_node* make_int_lit(struct ast_node * a);
struct ast_node* make_float_lit(struct ast_node * a);
struct ast_node* make_identifier(struct ast_node * a);
struct ast_node* make_lval_identifier(struct ast_node *text);

struct magic_object* ast_execute(m_state * state, struct ast_node* node);