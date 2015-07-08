#define INT_OBJ 0
#define STRING_OBJ 1
#define TABLE_OBJ 2
#define FUNCTION_OBJ 3
#define DOUBLE_OBJ 4
#define MODULE_OBJ 5
#define NILL_OBJ    6

struct magic_object;
struct magic_context;
struct magic_hash_table;

#ifndef MAGIC_OBJECT_DEFINED
#define MAGIC_OBJECT_DEFINED
struct magic_object {    
    short type;
    void *value;
};
#endif
typedef struct magic_object m_object;

#ifndef MAGIC_HASH_ENTRY_DEFINED
#define MAGIC_HASH_ENTRY_DEFINED
struct magic_hash_entry {
    struct magic_hash_entry *next;
    char *key;
    m_object *value;
};
#endif
typedef struct magic_hash_entry m_hashentry;

#ifndef MAGIC_HASH_TABLE_DEFINED
#define MAGIC_HASH_TABLE_DEFINED
struct magic_hash_table {
    struct magic_hash_entry** table;
    unsigned int size;
};
#endif
typedef struct magic_hash_table m_hash_table;

#ifndef MAGIC_NAMESPACE_DEFINED
#define MAGIC_NAMESPACE_DEFINED
struct magic_namespace {
    struct magic_namespace* next_namespace;
    struct magic_hash_table* namespace_table;
};
#endif
typedef struct magic_namespace m_namespace;

#ifndef MAGIC_STATE_DEFINED
#define MAGIC_STATE_DEFINED
struct magic_state {
    struct magic_namespace* global_namespace;
    struct magic_namespace* cur_namespace;
};
#endif
typedef struct magic_state m_state;

m_object* get_identifier(char *identifier);

m_object* make_magic_object(char *string);
m_object* make_magic_object(int value);
m_object* make_magic_object(double value);
void free_magic_object(m_object *obj);
