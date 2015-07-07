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

void set_identifier(char identifier,  m_object* value) {

}

m_object* get_identifier(char *identifier) {
    return NULL;
}