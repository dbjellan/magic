#include <stdlib.h>
#include <string.h>

#include "magic.h"
#include "data.h"

m_object* make_magic_object(char *string) {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        char *newstr = (char *) malloc(strlen(string));
        result->type = STRING_OBJ;
        if (newstr != NULL) {
            strcpy(newstr, string);
            result->value = (void *)newstr;
        }
    }
    return result;
}

m_object* make_magic_object(int value) {
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

m_object* make_magic_object(double value) {
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

void free_magic_object(m_object *obj) {
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
    }
    return newstate;

}


void set_identifier(m_state* state, char *identifier,  m_object* value) {
    m_namespace *ns = state->cur_namespace;
    set(ns->namespace_table, identifier, value);
}

m_object** get_lvalue(m_state* state, char *identifier) {
    m_namespace *ns = state->cur_namespace;
    m_object **result = NULL;
    while(ns != NULL && (*result = get(ns->namespace_table, identifier)) == NULL) {
        ns = ns->next_namespace;
    }
    return result;
}

m_object* get_identifier(m_state* state, char *identifier) {
    m_namespace *ns = state->cur_namespace;
    m_object *result = NULL;
    while(ns != NULL && (result = get(ns->namespace_table, identifier)) == NULL) {
        ns = ns->next_namespace;
    }
    return result;
}
