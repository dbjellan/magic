#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "magic.h"
#include "data.h"
#include "util.h"

#define INT_STRING_LENGTH 20
#define DOUBLE_STRING_LENGTH 20

void raise_uncaught(m_state *state) {
    fatal("[*] Uncaught exception!");
}

int register_exception(m_state *state) {
    int result;
    struct handler_entry* handler = (struct handler_entry*) malloc(sizeof(struct handler_entry));
    if (handler) {
        if((result = setjmp(handler->buf)) == 0) {
            handler->next = state->catch_stack;
            //jmp_buf buf = 
            state->catch_stack = handler;
            return 0;
        }
        return result;
    } else {
        return -1;
    }
}

void pop_exception(m_state *state) {
    if (state->catch_stack != NULL) {
        struct handler_entry* new_top;
        new_top = state->catch_stack->next;
        free(state->catch_stack);
        state->catch_stack = new_top;
    }
}

m_object* make_nill_object() {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        result->type = NILL_OBJ;
        result->value = NULL;
    }
    return result;    
}

m_object* make_ident_object(char *ident) {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        result->type = IDENT_OBJ;
        result->value = malloc(strlen(ident)+1);
        strcpy((char *)result->value, ident);
    }
    return result;
}

m_object* make_ref_object(m_object** ref) {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        result->type = REF_OBJ;
        result->value = (void *)ref;
    }

    return result;
}

m_object* make_string_object(char *string) {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        char *newstr = (char *) malloc(strlen(string)+1);
        result->type = STRING_OBJ;
        if (newstr != NULL) {
            strcpy(newstr+1, string);
            result->value = (void *)newstr;
        }
    }
    return result;
}

m_object* make_int_object(int value) {
    m_object* result = (m_object*) malloc(sizeof(m_object));   
    if (result != NULL) {
        int *valueptr = (int *) malloc(sizeof(int));
        result->type = INT_OBJ;
        if (valueptr != NULL) {
            *valueptr = value;
            result->value = (void *)valueptr;
        }
    }
    return result;
}

m_object* make_double_object(double value) {
    m_object* result = (m_object*) malloc(sizeof(m_object));   
    if (result != NULL) {
        double *valueptr = (double *) malloc(sizeof(double));
        result->type = DOUBLE_OBJ;
        if (valueptr != NULL) {
            *valueptr = value;
            result->value = (void *)valueptr;
        }
    }
    return result;
}

m_object* make_function_object(char **args, ast_node* code) {
    m_object* result = (m_object*) malloc(sizeof(m_object));   
    if (result != NULL) {
        m_function* function = (m_function*) malloc(sizeof(m_function));
        function->fcode.node = code;
        function->arglist = args;
        result->value = (void *)function;
        result->type = FUNCTION_OBJ;
    }
    return result;
}

void free_magic_object(m_object *obj) {
    if (obj->type != REF_OBJ)
        free(obj->value);
    free(obj);
}

void load_builtins(m_namespace *np) {

}

m_namespace* new_global_namespace() {
    m_namespace *newglobal = (m_namespace *)malloc(sizeof(m_namespace));
    if (newglobal) {
        newglobal->next_namespace = NULL;
        newglobal->namespace_table = new_hash_table(7);
    }
    load_builtins(newglobal);
    return newglobal;
}

m_state* new_magic_state() {
    m_state *newstate = (m_state *)malloc(sizeof(m_state));
    m_namespace *newglobalns = new_global_namespace();
    if (newstate) {
        newstate->global_namespace = newglobalns;
        newstate->cur_namespace = newglobalns;
        newstate->cur_exception = NULL;
        newstate->catch_stack = NULL;
    }
    return newstate;

}

void push_scope(m_state *state) {
    return;
}

void pop_scope(m_state *state) {
    return ;
}

void set_identifier(m_state* state, char *identifier,  m_object* value) {
    m_namespace *ns = state->cur_namespace;
    set(ns->namespace_table, identifier, value);
}

m_object** get_lvalue(m_state* state, char *identifier) {
    m_namespace *ns = state->cur_namespace;
    m_object **result_obj = NULL;
    result_obj = get_lvalue(ns->namespace_table, identifier);
    while(ns != NULL && result_obj == NULL) {
        result_obj =  get_lvalue(ns->namespace_table, identifier);
        ns = ns->next_namespace;
    }
    return result_obj;
}

m_object* get_identifier(m_state* state, char *identifier) {
    m_namespace *ns = state->cur_namespace;
    m_object *result = NULL;
    while(ns != NULL && (result = get(ns->namespace_table, identifier)) == NULL) {
        ns = ns->next_namespace;
    }
    if (result != NULL) {
        return result;
    } else {
        return make_nill_object();
    }
}

m_object* assign(m_state *state, m_object *lexp, m_object* rvalue) {
    if (lexp->type == REF_OBJ) {
        m_object **lvalue = (m_object **) lexp->value;
        *lvalue = rvalue;
        free_magic_object(lexp);
    } else {
        // object is IDENT_OBJ
            set_identifier(state, (char *)lexp->value, rvalue);
    }
    return rvalue;
}

char *magic_object_tostring(m_object *obj) {
    char *result;
    switch (obj->type) {
        case NILL_OBJ: {
            char *nill_string = "nill";
            result = (char *) malloc(strlen(nill_string)+1);
            strcpy(result, nill_string);
            break;
        }
        case INT_OBJ:
            result = (char *) malloc(INT_STRING_LENGTH);
            snprintf(result, INT_STRING_LENGTH, "%d", *(int *)obj->value);
            break;
        case DOUBLE_OBJ:
            result = (char *) malloc(DOUBLE_STRING_LENGTH);
            snprintf(result, DOUBLE_STRING_LENGTH, "%f", *(double *)obj->value);
            break;
        case STRING_OBJ:
            result = (char *) malloc(strlen((char *) obj->value)+3);
            sprintf(result, "\"%s\"", result);
            break;
    }
    return result;
}