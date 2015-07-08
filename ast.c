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

struct ast_node* make_string_lit(char *text) {
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    char *value = (char *) malloc(strlen(text)+1);
    strcpy(value, text);
    result->children = NULL;
    result->type = AST_STRING_LIT;
    result->value = (void *) value;
    return result;
}

struct ast_node* make_int_lit(char *text) {
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

struct ast_node* make_float_lit(char *text) {
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

struct ast_node* make_identifier(char *text) {

}

struct ast_node* make_field(char *text) {

} 

struct ast_node* make_add(struct ast_node * a, struct ast_node *b) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->type = AST_ADD;
    result->children = (struct ast_node **) malloc(sizeof(struct ast_node*)*2);
    result->children[0] = a;
    result->children[1] = b;
    result->children[2] = NULL;
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

struct ast_node* make_lval_identifier(char * text) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    char *ptr = (char *) malloc(strlen(text)+1);
    strcpy(ptr, text);
    result->type = AST_ASSIGN;
    result->children = NULL;
    result->value = ptr;
    return result;
}

void free_ast_node(struct ast_node *node) {
    if (node != NULL) {
        if (node->children != NULL){
            struct ast_node *child = node->children[0];
        }
    }
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
            m_object **lvalue = (m_object **) rexp->value.ptr;
            m_object *rvalue = execute_ast(state, node->children[1]);
            *lvalue = rvalue;
            free_magic_object(*lvalue);
            return rvalue;
        }

        default:
            fatal("Illegal internal state");
    }
}
