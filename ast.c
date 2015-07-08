#include <stdlib.h>
#include <string.h>

#include "magic.h"
#include "ast.h"
#include "util.h"

struct ast_node {
    struct ast_node **children;
    short int type;
    void * value;
};

struct ast_node* make_ast_node(int numchildren, int type) {
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    if (numchildren > 0) {
        struct ast_node **children = (struct ast_node **) malloc(sizeof(struct ast_node*)*numchildren+1);
        children[numchildren] = NULL;
        result->children = children;
    } else {
        result->children = NULL;
    }
    result->type = type;
    return result;
}

struct ast_node* make_string_lit(struct ast_node * a) {
    char *text = (char *) a;    
    struct ast_node* result = make_ast_node(0, AST_STRING_LIT);
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->value = (void *) value;
    return result;
}

struct ast_node* make_int_lit(struct ast_node *a) {
    char *text = (char *) a;
    int converted = atoi(text);
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    int *value = (int *) malloc(sizeof(int));
    *value = converted;
    result->children = NULL;
    result->type = AST_STRING_LIT;
    result->value = (void *) value;
    return result;
}

struct ast_node* make_float_lit(struct ast_node *a) {
    char *text = (char *) a;
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    double converted = atof(text);
    double *value = (double *) malloc(sizeof(double));
    *value = converted;
    result->children = NULL;
    result->type = AST_STRING_LIT;
    result->value = (void *) value;
    return result;
}

struct ast_node* make_identifier(struct ast_node *a) {
    char *text = (char *) a;
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->children = NULL;
    result->type = AST_IDENTIFIER;
    result->value = (void *) value; 
    return result;
}

struct ast_node* make_field(struct ast_node * a, struct ast_node * b) {
    char *text = (char *) b;
    struct ast_node* result = make_ast_node(2, AST_FIELD);
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->children[0] = a;
    result->children[1] = b;
    result->value = (void *) value;
    return result;    
} 

struct ast_node* make_lval_identifier(struct ast_node *a) {
    char *text = (char *) a;
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->children = NULL;
    result->type = AST_LVAL_IDENTIFIER;
    result->value = (void *) value; 
    return result;
}

struct ast_node* make_lval_access(struct ast_node * a, struct ast_node* b) {
    char *text = (char *) b;    
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->value = (void *) value;
    return result;
}

struct ast_node* make_add(struct ast_node * a, struct ast_node *b) {
    struct ast_node* result = make_ast_node(2, AST_ADD);
    result->children[0] = a;
    result->children[1] = b;
    return result;
}

struct ast_node* make_sub(struct ast_node * a, struct ast_node *b) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->type = AST_SUB;
    result->children = (struct ast_node **) malloc(sizeof(struct ast_node*)*3);
    result->children[0] = a;
    result->children[1] = b;
    result->children[2] = NULL;
    return result;
}

struct ast_node* make_mult(struct ast_node * a, struct ast_node *b) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->type = AST_MULT;
    result->children = (struct ast_node **) malloc(sizeof(struct ast_node*)*3);
    result->children[0] = a;
    result->children[1] = b;
    result->children[2] = NULL;
    return result;
}

struct ast_node* make_div(struct ast_node* a, struct ast_node* b) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->type = AST_DIV;
    result->children = (struct ast_node **) malloc(sizeof(struct ast_node*)*3);
    result->children[0] = a;
    result->children[1] = b;
    result->children[2] = NULL;
    return result;
}

struct ast_node* make_assign(struct ast_node* lvalue, struct ast_node* rvalue) {
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->type = AST_ASSIGN;
    result->children = (struct ast_node **) malloc(sizeof(struct ast_node*)*3);
    result->children[0] = lvalue;
    result->children[1] = rvalue;
    result->children[2] = NULL;
    return result;
}

struct ast_node* make_func(struct ast_node *ident, struct ast_node *arglist, struct ast_node *body) {
    struct ast_node* result = make_ast_node(3, AST_FUNC);
    result->children[0] = ident;
    result->children[1] = arglist;
    result->children[2] = body;
    return result;
}
struct ast_node* make_function_call(struct ast_node *ident, struct ast_node *arglist) {
    struct ast_node* result = make_ast_node(2, AST_FUNCTION_CALL);
    result->children[0] = ident;
    result->children[1] = arglist;
    return result;    
}
struct ast_node* make_module(struct ast_node *statements) {
    struct ast_node* result = make_ast_node(1, AST_MODULE);
    result->children[0] = statements;
    return result;      
}

struct ast_node* make_statements(struct ast_node *s1, struct ast_node *s2) {
    struct ast_node* result = make_ast_node(2, AST_STATEMENTS);
    result->children[0] = s1;
    result->children[1] = s2;
    return result;      
}

struct ast_node* make_varlist(struct ast_node *a, struct ast_node *b) {
    struct ast_node* result = make_ast_node(2, AST_VARLIST);
    result->children[0] = a;
    result->children[1] = b;
    return result;      
}

struct ast_node* make_arglist(struct ast_node *a, struct ast_node *b) {
    struct ast_node* result = make_ast_node(2, AST_ARGLIST);
    result->children[0] = a;
    result->children[1] = b;
    return result;      
}

void free_ast_node(struct ast_node *node) {
    if (node->children != NULL) {
        struct ast_node *child = node->children[0];
        while(child != NULL) {
            free(child);
            child++;
        }
    }
    free(node);
}

struct magic_object* execute_ast(m_state * state, struct ast_node* node) {
    struct magic_object* result = NULL;
    switch (node->type) {
        case AST_STRING_LIT:
            result = make_magic_object((char *)node->value);
            return result;
        case AST_INT_LIT:
            result = make_magic_object(*(int *)node->value);
            return result;
        case AST_FLOAT_LIT:
            result = make_magic_object(*(double *)node->value);
            return result;
        case AST_ASSIGN: {
            magic_object *rexp = execute_ast(state, node->children[0]);
            m_object **lvalue = (m_object **) rexp->value;
            m_object *rvalue = execute_ast(state, node->children[1]);
            *lvalue = rvalue;
            free_magic_object(*lvalue);
            return rvalue;
        }

        default:
            fatal("Illegal internal state");
    }
}
