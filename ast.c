#include <stdlib.h>
#include <stdio.h>
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
    result->type = AST_INT_LIT;
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
    result->type = AST_FLOAT_LIT;
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
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->children = NULL;
    result->type = AST_LVAL_IDENTIFIER;
    result->value = (void *) a; 
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
    free(node->value);
    free(node);
}

struct magic_object* ast_execute_add(m_state * state, struct ast_node* node) {
    struct magic_object* result;
    magic_object* a = ast_execute(state, node->children[0]);
    magic_object* b = ast_execute(state, node->children[1]);
    if ((a->type == DOUBLE_OBJ ||a->type == INT_OBJ ) && (b->type == INT_OBJ || b->type == DOUBLE_OBJ )) {
        if (a->type == DOUBLE_OBJ || b->type == DOUBLE_OBJ) {
        double result_val = 0;
        result_val = *(double *)node->children[0]->value + *(double *)node->children[1]->value;
        result = make_double_object(result_val);
        } else {
            int result_val = 0;
            result_val = *(int *)node->children[0]->value + *(int *)node->children[1]->value;
            result = make_int_object(result_val);
        }
    } else {
        fatal("can't add objects, raise exception here");
    }
    return result;
}

struct magic_object* ast_execute_lval_ident(m_state * state, struct ast_node* node) {
    char* identifier = (char *)node->value;
    m_object** val = get_lvalue(state, identifier);
    m_object* result;
    if (val == NULL) {
        result = make_ident_object(identifier);
    }
    else {
        result = make_ref_object(val);
    }
    return result;
}

struct magic_object* ast_execute(m_state * state, struct ast_node* node) {
    struct magic_object* result = NULL;
    switch (node->type) {
        case AST_STRING_LIT:
            result = make_string_object((char *)node->value);
            return result;
        case AST_INT_LIT:
            result = make_int_object(*(int *)node->value);
            return result;
        case AST_FLOAT_LIT:
            result = make_double_object(*(double *)node->value);
            return result;
        case AST_ADD:
            return ast_execute_add(state, node);
        case AST_ASSIGN: {
            magic_object *lexp = ast_execute(state, node->children[0]);
            m_object *rvalue = ast_execute(state, node->children[1]);
            if (lexp->type == REF_OBJ) {
                m_object **lvalue = (m_object **) lexp->value;
                *lvalue = rvalue;
                free_magic_object(lexp);
            } else {
                // object is IDENT_OBJ
                printf("setting new identifier");
                set_identifier(state, (char *)lexp->value, rvalue);
            }
            return rvalue;
        }
        case AST_LVAL_IDENTIFIER: 
            return ast_execute_lval_ident(state, node);
        case AST_MODULE:
            return ast_execute(state, node->children[0]);
        case AST_IDENTIFIER:
            return get_identifier(state, (char *)node->value);
        default:
            fatal("Illegal internal state");
    }
}
