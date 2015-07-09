#include <stdlib.h>
#include <string.h>

#include "magic.h"
#include "data.h"

m_hash_table* new_hash_table(int size) {
    m_hash_table* table = (m_hash_table*) malloc(sizeof(m_hash_table));
    if (table) {
        table->table = (magic_hash_entry **) malloc(sizeof(struct magic_hash_entry**)*size);
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

m_object* get(m_hash_table *table, char *key) {
    unsigned int hash_value = hash(key, table->size);
    m_hashentry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            return bin_entry->value;
        }
        bin_entry = bin_entry->next;
    }
    return NULL;
}

m_object** get_lvalue(m_hash_table *table, char *key) {
    unsigned int hash_value = hash(key, table->size);
    m_hashentry *bin_entry = table->table[hash_value];
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            return &(bin_entry->value);
        }
        bin_entry = bin_entry->next;
    }
    return NULL;
}

m_object** get_lvalue(m_state *table, char *key) {

}

void resize(m_hash_table *table, unsigned int new_size) {
    m_hash_table* result;
    if (new_size > table->size) {
        unsigned int old_size = table->size;
        result = new_hash_table(new_size);
        m_hashentry *cur_entry;
        for(int i = 0; i < old_size; i++) {
            cur_entry = table->table[i];
            while(cur_entry != NULL) {
                set(result, cur_entry->key, cur_entry->value);
                cur_entry = cur_entry->next;
            }
        }
    }
}

void set(m_hash_table *table, char *key, m_object *value) {
    unsigned int hash_val = hash(key, table->size);
    m_hashentry *bin_entry = table->table[hash_val];
    bool found = false;
    while (bin_entry != NULL) {
        if (strcmp(key, bin_entry->key) == 0) {
            bin_entry->value = value;
            found = true;
            break;
        }
    } 
    if (!found) {
        bin_entry = (m_hashentry *)malloc(sizeof(m_hashentry));
        if (bin_entry) {
            bin_entry->next = NULL;
            bin_entry->key = key;
            bin_entry->value = value;
        }
    }
}
