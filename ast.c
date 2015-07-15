#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "magic.h"
#include "ast.h"
#include "util.h"

struct ast_node {
    struct ast_node **children;
    short int type;
    void * value;
};

struct ast_node* make_internal_node(int type, struct ast_node* a) {
    struct ast_node* result = make_ast_node(1, type);
    result->children[0] = a;
    result->value = NULL;
    return result;
}

struct ast_node* make_internal_node(int type, struct ast_node* a, struct ast_node* b) {
    struct ast_node* result = make_ast_node(2, type);
    result->children[0] = a;
    result->children[1] = b;
    return result;
}

struct ast_node* make_internal_node(int type, struct ast_node* a, struct ast_node* b, struct ast_node* c) {
    struct ast_node* result = make_ast_node(3, type);
    result->children[0] = a;
    result->children[1] = b;
    result->children[2] = c;
    result->value = NULL;
    return result;
}

struct ast_node* make_ast_node(int numchildren, int type) {
    struct ast_node* result;
    result = (struct ast_node*) malloc(sizeof(struct ast_node));
    if (numchildren > 0) {
        struct ast_node **children = (struct ast_node **) malloc(sizeof(struct ast_node*)*(numchildren+1));
        for (int i = 0; i < numchildren; i++) {
            children[i] = NULL;
        }
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

struct ast_node* make_lval_identifier(struct ast_node *a) {
    struct ast_node* result = (struct ast_node*) malloc(sizeof(struct ast_node));
    result->children = NULL;
    result->type = AST_LVAL_IDENTIFIER;
    result->value = (void *) a; 
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
    if ((a->type == DOUBLE_OBJ || a->type == INT_OBJ ) && (b->type == INT_OBJ || b->type == DOUBLE_OBJ )) {
        if (a->type == DOUBLE_OBJ || b->type == DOUBLE_OBJ) {
            double result_val;
            if (a->type == INT_OBJ) {
                result_val = *(int *)a->value + *(double *)b->value;
            } else if (b->type == INT_OBJ) {
                result_val = *(double *)a->value + *(int *)b->value;
            }
            else {
                result_val = *(double *)a->value + *(double *)b->value;
            }
            result = make_double_object(result_val);
        } else {
            int result_val = 0;
            result_val = *(int *)a->value + *(int *)b->value;
            result = make_int_object(result_val);
        }
    } else {
        fatal("can't add objects, raise exception here");
    }
    return result;
}

struct magic_object* ast_execute_sub(m_state * state, struct ast_node* node) {
    struct magic_object* result;
    magic_object* a = ast_execute(state, node->children[0]);
    magic_object* b = ast_execute(state, node->children[1]);
    if ((a->type == DOUBLE_OBJ || a->type == INT_OBJ ) && (b->type == INT_OBJ || b->type == DOUBLE_OBJ )) {
        if (a->type == DOUBLE_OBJ || b->type == DOUBLE_OBJ) {
            double result_val;
            if (a->type == INT_OBJ) {
                result_val = *(int *)a->value - *(double *)b->value;
            } else if (b->type == INT_OBJ) {
                result_val = *(double *)a->value - *(int *)b->value;
            }
            else {
                result_val = *(double *)a->value - *(double *)b->value;
            }
            result = make_double_object(result_val);
        } else {
            int result_val = 0;
            result_val = *(int *)a->value - *(int *)b->value;
            result = make_int_object(result_val);
        }
    } else {
        fatal("can't add objects, raise exception here");
    }
    return result;
}

struct magic_object* ast_execute_mult(m_state * state, struct ast_node* node) {
    struct magic_object* result;
    magic_object* a = ast_execute(state, node->children[0]);
    magic_object* b = ast_execute(state, node->children[1]);
    if ((a->type == DOUBLE_OBJ || a->type == INT_OBJ ) && (b->type == INT_OBJ || b->type == DOUBLE_OBJ )) {
        if (a->type == DOUBLE_OBJ || b->type == DOUBLE_OBJ) {
            double result_val;
            if (a->type == INT_OBJ) {
                result_val = *(int *)a->value * *(double *)b->value;
            } else if (b->type == INT_OBJ) {
                result_val = *(double *)a->value * *(int *)b->value;
            }
            else {
                result_val = *(double *)a->value * *(double *)b->value;
            }
            result = make_double_object(result_val);
        } else {
            int result_val = 0;
            result_val = *(int *)a->value * *(int *)b->value;
            result = make_int_object(result_val);
        }
    } else {
        fatal("can't add objects, raise exception here");
    }
    return result;
}

struct magic_object* ast_execute_div(m_state * state, struct ast_node* node) {
    struct magic_object* result;
    magic_object* a = ast_execute(state, node->children[0]);
    magic_object* b = ast_execute(state, node->children[1]);
    if ((a->type == DOUBLE_OBJ || a->type == INT_OBJ ) && (b->type == INT_OBJ || b->type == DOUBLE_OBJ )) {
        if (a->type == DOUBLE_OBJ || b->type == DOUBLE_OBJ) {
            double result_val;
            if (a->type == INT_OBJ) {
                result_val = *(int *)a->value / *(double *)b->value;
            } else if (b->type == INT_OBJ) {
                result_val = *(double *)a->value / *(int *)b->value;
            }
            else {
                result_val = *(double *)a->value / *(double *)b->value;
            }
            result = make_double_object(result_val);
        } else {
            int result_val = 0;
            result_val = *(int *)a->value / *(int *)b->value;
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

struct magic_object *ast_execute_lval(m_state * state, struct ast_node* node) {
    struct ast_node* cur_node = node;
    if (node->type == AST_LVAL_ACCESS) {
        m_object *a = ast_execute_lval(state, node->children[0]);
        m_object *b = ast_execute_lval(state, node->children[1]);
        if (a->type == REF_OBJ) {
            
        }
    } else if(node->type == AST_LVAL_IDENTIFIER) {

    }
}

struct magic_object* ast_execute_trycatch(m_state * state, struct ast_node* node) {
    struct magic_object *exception;
    struct magic_object *result;
    if (register_exception(state) == 0) {
        result = ast_execute(state, node->children[0]);
        pop_exception(state);
    } else {
        pop_exception(state);
        push_scope(state);
        if (state->cur_exception != NULL)
            set_identifier(state, node->children[1]->value, state->cur_exception);
        result = ast_execute(state, node->children[2]);
        pop_scope(state);
    }
    return result;
}

struct magic_object* ast_execute_throw(m_state * state, struct ast_node* node) {
    if (state->catch_stack != NULL) {
        struct magic_object* val = ast_execute(state, node->children[0]);
        state->cur_exception = val;
        longjmp(state->catch_stack->buf, 1);
    } else {
        raise_uncaught(state);
    }
}

char ** make_arglist(struct ast_node* node) {

}

struct magic_object* ast_execute_function(m_state * state, struct ast_node* node) {
    char **arglist = make_arglist(node->children[1]);
    magic_object* func = make_magic_function(arglist, node->children[2]);
}

void new_cstack(m_state *state, struct ast_node* node) {

}

m_object *make_result_table(m_state *state, int numresults) {

}

struct magic_object* ast_execute_function_call(m_state * state, struct ast_node* node) {
    struct magic_object* result;
    struct magic_object* func_obj = ast_execute_lval(state, node->children[0]);
    if (func_obj->type == CFUNCTION_OBJ) {
        new_cstack(state, node->children[1]);
        magic_cfunction func = func_obj->value;
        int numresults = func(state);
        result = make_result_table(state, numresults);
    } else {
        push_scope(state);
        m_function *func = func_obj->value;
        result = ast_execute(state, func->fcode.node);
        pop_scope(state);
    }
    return result;
}


/* Execute ast and return and print and return any uncaught exceptions.
 *
 */
struct magic_object* protected_ast_execute(m_state * state, struct ast_node* node) {
    struct magic_object *result;
    if (register_exception(state) == 0) {
        result = ast_execute(state, node);
    } else {
        if (state->cur_exception != NULL) {
            result = state->cur_exception;
        } else {
            printf("[*] Unknown uncaught exception.\n");
            result  = make_nill_object();
        }
    }
    return result;
}

struct magic_object* ast_execute(m_state * state, struct ast_node* node) {
    struct magic_object* result = NULL;
    //printf("executing node %d\n", node->type);
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
        case AST_SUB:
            return ast_execute_sub(state, node);
        case AST_MULT:
            return ast_execute_mult(state, node);
        case AST_DIV:
            return ast_execute_div(state, node);
        case AST_FUNCTION:

        case AST_FUNCTION_CALL:
        case AST_STATEMENTS:
        case AST_IF_ELSE:
        case AST_IF:
        case AST_FOR:
        case AST_WHILE:
        case AST_TRY_CATCH:
        case AST_THROW:
        case AST_ELSE:
        case AST_ELSEIF_ELSE:
        case AST_ASSIGN: {
            m_object *lexp = ast_execute_lval(state, node->children[0]);
            m_object *rvalue = ast_execute(state, node->children[1]);
            return assign(state, lexp, rvalue);
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