#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INT 0
#define STRING 1
#define TABLE 2
#define FUNCTION 3
#define DOUBLE 4

struct magic_object;
struct magic_context;

union magic_value {
    char *as_string;
    int   *as_int;
    double *as_double;
    void *as_function;
    void *as_table;
};

struct magic_object {    
    short type;
    union magic_value value;
};

typedef struct magic_object m_object;

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

struct magic_context {
    struct magic_namespace* global_namespace;
    struct magic_namespace* top_namespace;
};


typedef struct magic_hash_entry m_hashentry;
typedef struct magic_hash_table m_hashtable;

typedef struct magic_object* (*magic_function)(struct magic_context*, struct magic_object**, int numargs);

void set(m_hashtable *table, char *key, m_object *value);

m_hashtable* new_hash_table(int size) {
    m_hashtable* table = malloc(sizeof(m_hashtable));
    if (table) {
        table->table = malloc(sizeof(struct magic_hash_entry*)*size);
        table->size = size;
    }
}

unsigned int hash(const char *key, unsigned int m) {
    size_t length = strlen(key);
    unsigned int value = NULL;
    int i = 0;
    unsigned int result = 0;
    unsigned int highorder = 0;
    while (i*4 < length) {
        value = ((unsigned int *)key)[i];
        highorder = result & 0xf8000000;
        result = result << 5;
        result = result ^ (highorder >> 27);
        result = result ^ value;
        i++;
    }
    if (length % 4 != 0) {
        value = 0;
        memcpy((void *) &value, (void *) key[4*(i-1)], length % 4);
        highorder = result & 0xf8000000;
        result = result << 5;
        result = result ^ (highorder >> 27);
        result = result ^ value;
    }
    return result;
}

m_object* get(m_hashtable *table, char *key) {
    unsigned int hash_value = hash(key, table->size);
    m_entry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            return bin_entry->value;
        }
        bin_entry = bin_entry->next;
    }
    return NULL;
}

void resize(m_hashtable *table, unsigned int new_size) {
    m_hashtable* result;
    if (new_size > table->size) {
        unsigned int old_size = table->size;
        m_hashtable *result;
        result = new_hash_table(new_size);
        m_entry *cur_entry;
        for(int i = 0; i < old_size; i++) {
            cur_entry = table->table[i];
            while(cur_entry != NULL) {
                set(result, cur_entry->key, cur_entry->value);
                cur_entry = cur_entry->next;
            }
        }
    }
}

void set(m_hashtable *table, char *key, m_object *value) {
    unsigned int hash_val = hash(key, table->size);
    m_entry *bin_entry = table->table[hash_val];
    bool found = false;
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            bin_entry->value = value;
            found = true;
            break;
        }
    } 
    if (!found) {
        bin_entry = malloc(sizeof(m_entry));
        if (bin_entry) {
            bin_entry->next = NULL;
            bin_entry->key = key;
            bin_entry->value = value;
        }
    }
}

m_object* get_identifier(char *identifier) {
    return NULL;
}
