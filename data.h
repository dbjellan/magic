#include "magic.h"

void set(m_hash_table *table, char *key, m_object *value);
m_object* get(m_hash_table *table, char *key);
m_hash_table* new_hash_table(int size);