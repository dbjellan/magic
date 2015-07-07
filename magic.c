#include <stdlib.h>
#include <string.h>

#include "magic.h"

union magic_value {
    char *as_string;
    int   *as_int;
    double *as_double;
    void *as_function;
    void *as_table;
    void *ptr;
};

struct magic_object {    
    short type;
    union magic_value value;
};

struct magic_hash_entry {
    struct magic_hash_entry *next;
    char *key;
    m_object *value;
};
typedef struct magic_hash_entry m_entry;

struct magic_hash_table {
    struct magic_hash_entry** table;
    unsigned int size;
};

struct magic_namespace {
    struct magic_namespace* next_namespace;
    struct magic_hash_table* namespace_table;
};
typedef struct magic_namespace magic_namespace;

struct magic_state {
    struct magic_namespace* global_namespace;
    struct magic_namespace* cur_namespace;
    struct vm_instruction *instructions;
};
typedef struct magic_state m_state;

typedef struct magic_hash_entry m_hashentry;
typedef struct magic_hash_table m_hashtable;

struct magic_function {
    
};

m_object* make_magic_object(char *string) {
    m_object* result = (m_object*) malloc(sizeof(m_object));
    if (result != NULL) {
        char *newstr = (char *) malloc(strlen(string));
        result->type = STRING;
        if (newstr != NULL) {
            strcpy(newstr, string);
            result->value.as_string = newstr;
        }
    }
    return result;
}

m_object* make_magic_object(int value) {
    m_object* result = (m_object*) malloc(sizeof(m_object));   
    if (result != NULL) {
        int *valueptr = (int *) malloc(sizeof(int));
        result->type = INT;
        if (valueptr != NULL) {
            *valueptr = value;
            result->value.as_int = valueptr;
        }
    }
    return result;
}

m_object* make_magic_object(double value) {
    m_object* result = (m_object*) malloc(sizeof(m_object));   
    if (result != NULL) {
        double *valueptr = (double *) malloc(sizeof(double));
        result->type = DOUBLE;
        if (valueptr != NULL) {
            *valueptr = value;
            result->value.as_double = valueptr;
        }
    }
    return result;
}

void free_magic_object(m_object *obj) {
    switch (obj->type) {
        case INT:

        case DOUBLE:

        case STRING:

        default:
            free(obj->value.ptr);
    }
    free(obj);
}

void load_builtins(m_namespace *np) {

}

m_namespace* new_global_namespace() {
    m_namespace *newglobal = (m_namespace *)malloc(sizeof(m_namespace));
    if (newglobal) {
        newglobal->next = NULL;
        newglobal->namespace_table = new_hash_table(7);
    }
    load_builtins(newglobal);
    return newglobal;
}

m_state* new_magic_state() {
    m_state *newstate = (m_state *)malloc(sizeof(m_state));
    m_namespace *newglobalns = new_global_namespace();
    if (m_state) {
        newstate->global_namespace = newglobalns;
        newstate->cur_namespace = newglobalns;
    }
    newstate->instructions = NULL;
    return newstate;

}


void set_identifier(m_state* state, char identifier,  m_object* value) {
    m_namespace ns = state->cur_namespace;
    set(ns->namespace_table, identifier, value);
}

m_object** get_lvalue(m_state* state, char identifier) {
    m_namespace ns = state->cur_namespace;
    m_object **result = NULL;
    while(ns != NULL && (result = get_lvalue(ns->namespace_table, identifier)) == NULL) {
        ns = ns->next_namespace;
    }
    return result;
}

m_object* get_identifier(m_state* state, char *identifier) {
    m_namespace ns = state->cur_namespace;
    m_object *result = NULL;
    while(ns != NULL && (result = get(ns->namespace_table, identifier)) == NULL) {
        ns = ns->next_namespace;
    }
    return result;
}
