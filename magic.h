#include <setjmp.h>

#define INT_OBJ 0
#define STRING_OBJ 1
#define TABLE_OBJ 2
#define FUNCTION_OBJ 3
#define DOUBLE_OBJ 4
#define MODULE_OBJ 5
#define NILL_OBJ    6
#define CFUNCTION_OBJ 7
// for internal use only
#define REF_OBJ     8
#define IDENT_OBJ   9

struct magic_object;
struct magic_context;
struct magic_hash_table;

#ifndef MAGIC_OBJECT_DEFINED
#define MAGIC_OBJECT_DEFINED
struct magic_object {    
    int type;
    void *value;
};
#endif
typedef struct magic_object m_object;


#ifndef MAGIC_NAMESPACE_DEFINED
#define MAGIC_NAMESPACE_DEFINED
struct magic_namespace {
    struct magic_namespace* next_namespace;
    struct magic_hash_table* namespace_table;
};
#endif
typedef struct magic_namespace m_namespace;

#ifndef MAGIC_HANDLER_ENTRY_DEFINED
#define MAGIC_HANDLER_ENTRY_DEFINED
struct handler_entry {
    struct handler_entry *next;
    jmp_buf buf; 
};
#endif

#ifndef MAGIC_STATE_DEFINED
#define MAGIC_STATE_DEFINED
struct magic_state {
    struct magic_namespace* global_namespace;
    struct magic_namespace* cur_namespace;
    struct handler_entry*   catch_stack;
    struct magic_object*    cur_exception;
};
#endif
typedef struct magic_state m_state;

#ifndef CODE_DEFINED
#define CODE_DEFINED
union code {
    struct ast_node* node;
};
#endif

#ifndef MAGIC_FUNCTION_DEFINED
#define MAGIC_FUNCTION_DEFINED
struct magic_function {
    char **arglist;
    union code fcode;
};
#endif
typedef magic_function m_function;

typedef int (*magic_cfunction)(m_state *state);

m_object* get_identifier(m_state * state, char *identifier);

m_object* make_string_object(char *string);
m_object* make_int_object(int value);
m_object* make_double_object(double value);
m_object* make_ident_object(char *ident);
m_object* make_ref_object(m_object** ref);
m_object* make_nill_object();


m_state* new_magic_state();
int register_exception(m_state *state);
void pop_exception(m_state *state);
void raise_uncaught(m_state *state);

void free_magic_object(m_object *obj);
char *magic_object_tostring(m_object *ojb);
m_object** get_lvalue(m_state* state, char *identifier);
void set_identifier(m_state* state, char *identifier,  m_object* value);
