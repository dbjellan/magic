
#include "magic.h"

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

void set(m_hash_table *table, char *key, m_object *value);
m_object* get(m_hash_table *table, char *key);
m_object** get_lvalue(m_hash_table *table, char *key);
m_hash_table* new_hash_table(int size);
void destroy_hash_table(m_hash_table *table);
void resize(m_hash_table *table, unsigned int new_size);
void print_table(m_hash_table *table);